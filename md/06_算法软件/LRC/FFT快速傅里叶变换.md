# 快速傅里叶变换（FFT）应用解析

## 📖 简介

本文档解析了基于 **ARM CMSIS-DSP** 库实现快速傅里叶变换（FFT）的核心代码。旨在将时域上的ADC采样信号（如电压、电流）转换到频域，以分析其频谱特性。

---

## 🚀 核心代码实现

### 1️⃣ **步骤一：准备FFT输入数据**

FFT计算需要复数作为输入。我们首先需要将ADC采样到的实数数组转换为复数数组，其中实部为采样值，虚部为0。

```c
/**
 * @brief  将ADC采样数据（实数）转换为FFT所需的复数格式。
 * @param[in]  adc_data_v  电压信号的ADC采样数组 (uint16_t)
 * @param[in]  adc_data_i  电流信号的ADC采样数组 (uint16_t)
 * @note   FFT输入数组的长度是FFT点数的2倍，交错存储实部和虚部。
 *         [real0, imag0, real1, imag1, ...]
 */
static void fft_prepare_input(uint16_t *adc_data_v, uint16_t *adc_data_i)
{
    for (int i = 0; i < 128; i++) {
        // 电压信号：实部为ADC值，虚部为0
        fft_cmp[2 * i]     = (float)adc_data_v[i]; // Real part
        fft_cmp[2 * i + 1] = 0.0f;                  // Imaginary part
      
        // 电流信号：实部为ADC值，虚部为0
        fft_cmp2[2 * i]     = (float)adc_data_i[i]; // Real part
        fft_cmp2[2 * i + 1] = 0.0f;                   // Imaginary part
    }
}
```

### 2️⃣ **步骤二：执行FFT计算与后续处理**

此函数是FFT处理的主流程，包含：**数据准备 -> FFT变换 -> 幅值计算**。

```c
/**
 * @brief  执行FFT计算并获取频域幅值。
 */
static void fft_calculate_magnitude()
{
    // 步骤1: 将ADC数据转换为复数格式
    fft_prepare_input(count_val_v, count_val_i);

    // (可选) 可以在此处分析时域信号特性, 例如寻找最大值
    // arm_max_f32(real_signal_data, 128, &max_value, &max_index);

    // 步骤2: 执行FFT变换 (128点)
    // arm_cfft_f32 会在原数组上进行计算，结果覆盖输入数据
    arm_cfft_f32(&arm_cfft_sR_f32_len128, fft_cmp,  0 /*正变换*/, 1 /*使能位反转*/);
    arm_cfft_f32(&arm_cfft_sR_f32_len128, fft_cmp2, 0, 1);

    // 步骤3: 计算复数频谱的模值，得到频域幅值
    // 输入为128个复数，输出为128个幅值
    arm_cmplx_mag_f32(fft_cmp,  fft_out,  128); // 电压频谱幅值
    arm_cmplx_mag_f32(fft_cmp2, fft_out2, 128); // 电流频谱幅值
}
```
*原代码中的 `arm_max_f32` 函数被用在了复数数组上，这通常不是预期行为。它会寻找256个浮点数（128个实部和128个虚部）中的最大值。如果需要时域最大值，应在原始ADC数据上计算。*

---

## 🔍 关键函数与参数解析

| 函数 / 结构体              | 说明                                                         |
| -------------------------- | ------------------------------------------------------------ |
| `arm_cfft_f32()`           | **核心FFT函数**。对输入的复数数组执行原地（in-place）计算。    |
| `arm_cmplx_mag_f32()`      | 计算复数数组的**模值**（`sqrt(real^2 + imag^2)`），得到频谱幅值。 |
| `arm_cfft_sR_f32_len128`   | ARM官方提供的**128点FFT配置实例**。使用前需要初始化。         |
| `ifftFlag` (参数3)         | `0` 表示正向FFT（时域->频域），`1` 表示逆向IFFT（频域->时域）。 |
| `bitReverseFlag` (参数4)   | `1` 表示使能位反转，这是标准FFT算法的要求。                  |

---

## 📊 数据结构与频谱解读

### **数据定义**
```c
// 假设已定义的全局数组
#define FFT_POINTS 128

float fft_cmp[FFT_POINTS * 2];   // 电压信号复数数组 (128复数点 = 256浮点数)
float fft_cmp2[FFT_POINTS * 2];  // 电流信号复数数组
float fft_out[FFT_POINTS];       // 电压频谱幅值输出
float fft_out2[FFT_POINTS];      // 电流频谱幅值输出
```

### **频谱结果解读**

对于一个N点的实数信号FFT：
1.  **输出对称性**：`fft_out` 数组包含 `N` 个幅值，但对于实数输入，其频谱是共轭对称的。我们通常只关心前半部分。
2.  **有效数据**：
    *   `fft_out[0]`：**直流分量**。
    *   `fft_out[1]` 到 `fft_out[N/2 - 1]`：**交流分量**的幅值。
    *   `fft_out[N/2]`：**奈奎斯特频率**分量（如果N是偶数）。
3.  **频率分辨率**：每个点的频率 = `索引 * (采样频率 / N)`。例如，如果采样频率为 `12.8kHz`，则 `fft_out[1]` 对应 `1 * (12800 / 128) = 100Hz` 的频率分量。

---

## ⚠️ 注意事项

1.  **依赖库**：确保工程中已添加 **ARM CMSIS-DSP** 库 (`arm_math.h`)，并正确链接。
2.  **FFT实例初始化**：在使用 `arm_cfft_sR_f32_len128` 之前，必须先调用对应的初始化函数。
3.  **加窗函数**：为减少频谱泄露，通常在执行FFT前，需要对输入信号乘以一个窗函数（如汉宁窗）。此步骤应在 `fft_prepare_input` 函数中添加。
4.  **数据长度**：所有数组的长度必须严格匹配FFT点数，否则会导致计算错误或内存溢出。
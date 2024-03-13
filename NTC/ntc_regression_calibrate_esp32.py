import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

v_adc = np.array([  1.65, 2.53255814,
                    2.26875, 3.046153846,
                    2.121428571, 2.721052632,
                    0.503389831, 0.3,
                    3.156521739, 0.76744186,
                    1.03125, 0.253846154,
                    1.178571429, 0.578947368,
                    2.796610169, 3,
                    0.143478261],
                      dtype=np.float64)

v_real = np.array([ 1.58, 2.49,
                    2.2, 3.26, 
                    2.05, 2.71, 
                    0.42, 0.21, 
                    3.3, 0.67, 
                    0.95, 0.15, 
                    1.11, 0.49, 
                    2.8, 3.15, 
                    0.05],
                       dtype=np.float64)

def func2(x, a, b):
 return a * x + b


error = v_adc - v_real

popt, pcov = curve_fit(func2, v_adc, error)

max_error = np.max(np.abs(func2(v_adc, *popt) - error))
rms_error = np.sqrt(np.sum(np.power(func2(v_adc, *popt) - error, 2)) /
v_adc.shape[0])

print(f"Regression coefficients: {popt}")
print(f"Max error: {max_error:.3f}")
print(f"Quadratic mean error: {rms_error:.3f}")

x = np.linspace(0.00, 3.30, 1000)

plt.plot(v_adc, v_real, label="data")
plt.plot(v_adc, error, label="error")

plt.plot(x, func2(x, *popt), label="error function")

plt.plot(v_adc - func2(v_adc, *popt), v_real, label="result")

plt.title("ESP32 ADC calibration")
plt.xlabel("ADC read (V)")
plt.ylabel("Real voltage (V)")
plt.grid()
plt.show()
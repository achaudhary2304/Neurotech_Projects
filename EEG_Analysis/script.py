import numpy as np
from scipy import signal
import matplotlib.pyplot as plt


File_data = np.loadtxt(r"C:\Users\achau\Downloads\eeg-data.txt")


#Sample Frequency
fs = 100

# Defining  frequency bands
freq_bands = {'delta': (1, 4), 'theta': (4, 8), 'alpha': (8, 13), 'beta': (13, 30)}

# Calculating psd
frequencies, psd = signal.welch(File_data, fs, nperseg=1024)


# Compute the absolute bandpowers
absolute_bandpowers = {}
for band in freq_bands:
    freq_range = freq_bands[band]
    mask = (frequencies >= freq_range[0]) & (frequencies <= freq_range[1])
    absolute_bandpowers[band] = np.sum(psd[mask])

# Compute the total power
total_power = np.sum(list(absolute_bandpowers.values()))

# Compute the relative bandpowers
relative_bandpowers = {band: power / total_power for band, power in absolute_bandpowers.items()}


print("Absolute bandpowers:")
for band, power in absolute_bandpowers.items():
    print(f"{band}: {power}\n")
print("Total Power is ")
print(total_power)
print("\nRelative bandpowers:")
for band, power in relative_bandpowers.items():
    print(f"{band}: {power}")

#  Multitaper spectral analysis
from scipy.signal import spectrogram

#  time-halfbandwidth product for the DPSS window
NW = 3


# Multipaper Spectrogram
frequencies, times, Spectro = spectrogram(File_data, fs, window=('dpss', NW), nperseg=1024, noverlap=512)


# Calculating absolute bandpowers
absolute_bandpowers_mt = {}
for band in freq_bands:
    freq_range = freq_bands[band]
    mask = (frequencies >= freq_range[0]) & (frequencies <= freq_range[1])
    absolute_bandpowers_mt[band] = np.sum(Spectro[mask])

# Calculating total power
total_power_mt = np.sum(list(absolute_bandpowers_mt.values()))

# Calculating relative bandpower
relative_bandpowers_mt = {band: power / total_power_mt for band, power in absolute_bandpowers_mt.items()}


print("\nMultitaper absolute bandpowers:")
for band, power in absolute_bandpowers_mt.items():
    print(f"{band}: {power}")
print("\nMultitaper relative bandpowers:")
for band, power in relative_bandpowers_mt.items():
    print(f"{band}: {power}")
plt.semilogy(frequencies, Spectro)
plt.xlabel('Frequency (Hz)')
plt.ylabel('Amplitude ')
plt.title('Multipaper Spectrogram')
plt.show()
plt.semilogy(frequencies, psd)
plt.xlabel('Frequency (Hz)')
plt.ylabel('PSD (V^2/Hz)')
plt.title('Power Spectral Density (Welch)')
plt.show()

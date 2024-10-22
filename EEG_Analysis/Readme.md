# EEG Spectral Analysis Tool

## Overview
This Python script performs spectral analysis on EEG (electroencephalogram) data, calculating both traditional power spectral density using Welch's method and multitaper spectral analysis. The script analyzes different frequency bands (delta, theta, alpha, and beta) and computes both absolute and relative bandpowers.

## Features
* **Data Processing:**
  * Loads and processes EEG data from text files
  * Calculates power spectral density using Welch's method
  * Performs multitaper spectral analysis using DPSS windows

* **Frequency Band Analysis:**
  * Computes absolute and relative bandpowers for standard EEG frequency bands:
    * **Delta** (1-4 Hz)
    * **Theta** (4-8 Hz)
    * **Alpha** (8-13 Hz)
    * **Beta** (13-30 Hz)

* **Visualization:**
  * Generates visualizations of spectral analyses

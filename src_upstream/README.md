# QRSS
Repository containing monoband QRSS beacon programs with the following modulations: 
- **OOK (On-Off Keying):** Traditional CW/Morse modulation (QRSS_CW.ino).  
- **FSK / DFCW Morse:** Uses different frequencies for dots and dashes. Can be hard (QRSS_DFCW_H.ino) or soft keyed (QRSS_DFCW_S.ino).  
 
  
## Why Transmit at Very Slow Speeds (QRSS) in a Fast-Paced World?
Transmitting at very slow speeds has several advantages:
- **Lower bandwidth:** Signals occupy only ~1 Hz, enabling extremely stable transmission and reception.  
- **Greater distance for the same power:** The lower bandwidth allows propagation over longer distances with the same power, or equivalently, less power (QRP) is needed to cover the same distance.  
- **Lower noise:** Narrow bandwidth reduces the impact of noise.  
- **Feasible on extremely narrow amateur bands:** For example, 135.7–137.8 kHz where only 200 Hz bandwidth is available.

## QRSS Speeds

- QRSS speeds range from **3 seconds per dot (QRSS3)** up to **120 seconds per dot (QRSS120)**.  
- Example of performance improvement from "A comparison of QRSS modes, G3YXM: Some tests between G3YXM and G3NYK":  
  - QRSS60 over QRSS10 → +8 dB  
  - QRSS10 over QRSS3 → +7.6 dB  
  - QRSS3 over 12 ppm CW → +12 dB 
---
**Author:** Juanpa EA5JTT  
**Date:** 12/09/2025  
**Hardware Tested:** Lilygo T-Beam + Si5351

## Overview
The beacon QRSS DFCW sends the callsign `EA5JTT` in Morse code using a CW, frequency-shift keying (FSK) o FSK soft modulation with a small frequency sweep (chirp). 
The program is designed for very slow Morse (QRSS) modes and outputs the RF signal on CLK1 of the Si5351.

---

## Parameters

- **Callsign:** `EA5JTT` (provided directly as a symbol string, no Morse table conversion required)  
- **Modulation:** FSK with a frequency shift of +10 Hz  
- **Speed:** QRSS3 (3 seconds per symbol)  
- **Frequency:** 10.140,000 kHz (most popular QRSS band)  
- **RF Output:** CLK1  

---

## QRSS Operating Frequencies

| Band | QRSS Frequency (±100 Hz) | USB Dial (Hz) | Audio Frequency (Hz) |
|------|--------------------------|---------------|---------------------|
| 600m | 476.100 kHz              | 474,200       | 1,900               |
| 160m | 1,837.900 kHz            | 1,836,600     | 1,300               |
| 80m  | 3,569.900 kHz (popular)  | 3,568,600     | 1,300               |
| 60m  | 5,288.550 kHz            | 5,287,200     | 1,350               |
| 40m  | 7,039.900 kHz (popular)  | 7,038,600     | 1,300               |
| 30m  | 10,140.000 kHz (most popular) | 10,138,700 | 1,300            |
| 22m  | 13,555.400 kHz           | 13,553,900    | 1,300               |
| 20m  | 14,096.900 kHz (popular) | 14,095,600    | 1,300               |
| 17m  | 18,105.900 kHz           | 18,104,600    | 1,300               |
| 15m  | 21,095.900 kHz           | 21,094,600    | 1,300               |
| 12m  | 24,925.900 kHz           | 24,924,600    | 1,300               |
| 10m  | 28,125.700 kHz           | 28,124,600    | 1,100               |
| 6m   | 50,294.300 kHz           | 50,293,000    | 1,100               |

---
## Decoding and Visualization

Since CW, DFCW, and Multi-Tone Hell cannot be reliably decoded by ear, software is required:

- **FSKView (Windows):** Decodes received audio signals from QRSS and WSPR.  
- **Spectrum Lab:** Lab tool for audio spectrum analysis.  
- **Argo (Windows):** Decodes CW, DFCW, and QRSS, showing a waterfall display.  
- **LOPORA (Python, cross-platform):** Decodes QRSS audio.  
- **QRSSpig (Linux):** Decodes QRSS signals.  
- **LITOPO (Browser-based):** Waterfall viewer for QRSS, receives signal through audio channel, no installation required.

**Visualization Methods:**

- **Waterfall (cascading) view:** Vertical axis represents time.  
- **Curtain view:** Horizontal axis represents time.  

**Real-time Monitoring:** QRSS Plus allows live monitoring of QRSS transmissions (grabbers).  


**LITOPO Web Viewer:** [https://qsl.net/g0ftd/other/litopo/litopo1.htm](https://qsl.net/g0ftd/other/litopo/litopo1.htm)

** More information in spanish language: https://ea5jtt.blogspot.com/2025/12/qrss-transmsiones-muy-lentas.html

YOU MUST A AMATEUR LICENCE FOR RUN THIS PROGRAM

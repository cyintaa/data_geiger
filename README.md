# 📡 Data Pemantauan Radioaktivitas menggunakan Geiger Counter

## 📖 Deskripsi Proyek  
sistem **pemantauan radiasi berbasis Geiger counter** yang digunakan untuk mengukur tingkat radiasi lingkungan secara real-time. Data radiasi yang diperoleh dari Geiger akan dikumpulkan, disimpan, dan divisualisasikan untuk tujuan monitoring, penelitian.

Sistem ini dapat digunakan pada:
- Monitoring lingkungan sekitar industri nuklir  
- Pemantauan radioaktivitas wilayah publik  
- Penelitian fisika radiasi  
- Sistem peringatan dini radiasi  

---

## 🎯 Tujuan  
Tujuan dari pengembangan sistem ini adalah:  
- Mengumpulkan data radiasi (CPM/Bq/µSv/h) secara real-time  
- Menyimpan data ke database atau cloud  
- Menampilkan data monitoring dalam bentuk grafik/dashboard  
- Memberikan notifikasi jika radiasi melebihi ambang batas  
- Mendukung analisis data radiasi jangka panjang  

---

## ⚙️ Komponen Sistem  

### 🧪 Hardware
- Sensor Geiger Muller Tube  
- Modul Geiger Counter  
- ESP32 / Arduino / Raspberry Pi  
- GPS (opsional)  
- DHT22 (opsional suhu & kelembapan)  

### 💻 Software
- Firmware pembacaan sensor  
- Database (MySQL/Firebase/PostgreSQL)  
- Web dashboard monitoring  
- API pengiriman data  
- Visualisasi grafik  

---

## 📊 Format Data Pemantauan  

Contoh format data:

| Waktu | CPM | µSv/h | Suhu | Kelembapan | Lokasi |
|------|-----|-------|------|------------|--------|
| 2026-02-16 10:00 | 35 | 0.12 | 30°C | 70% | -7.9,112.6 |
| 2026-02-16 10:05 | 40 | 0.15 | 30°C | 71% | -7.9,112.6 |

Keterangan:
- **CPM** : Counts Per Minute  
- **µSv/h** : Dosis radiasi  
- **Bq** : Becquerel (opsional)  

---

## 🧠 Metode Sistem  
1. Sensor Geiger membaca pulsa radiasi  
2. Mikrokontroler menghitung CPM  
3. Konversi CPM → µSv/h  
4. Data dikirim ke database/server  
5. Dashboard menampilkan data real-time  

---

## 🚀 Fitur Utama  
- Monitoring radiasi real-time  
- Penyimpanan data historis  
- Grafik radiasi  
- IoT monitoring (WiFi/MQTT/LoRa)  
- Alarm ambang radiasi  
- Export data CSV/Excel  

---

## 📦 Struktur Repository

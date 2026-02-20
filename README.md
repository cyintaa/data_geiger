# 📡 Data Pemantauan Radioaktivitas menggunakan Geiger Counter

## 📖 Deskripsi 
sistem **pemantauan radiasi berbasis Geiger counter** yang digunakan untuk mengukur tingkat radiasi lingkungan secara real-time. Data radiasi yang diperoleh dari Geiger akan dikumpulkan, disimpan, dan divisualisasikan untuk tujuan monitoring, penelitian.

Sistem ini dapat digunakan pada:
- Monitoring lingkungan di atmosfir  
- Pemantauan radioaktivitas wilayah publik  
- Penelitian fisika radiasi  
- Sistem peringatan dini radiasi  

---

## 🎯 Tujuan  
Tujuan dari pengembangan sistem ini adalah:  
- Mengumpulkan data radiasi (CPM/Bq) secara real-time  
- Menyimpan data ke database atau cloud  
- Menampilkan data monitoring dalam bentuk grafik/dashboard  
- Memberikan notifikasi jika radiasi melebihi ambang batas  
- Mendukung analisis data radiasi jangka panjang  
---

## 📊 Format Data Pemantauan  
- format .txt
- isi : hh,mm,ss,index,cpm,temp,hum

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

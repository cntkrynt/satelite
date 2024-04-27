## Satelite Prototype Using SIM800l Module with SMS as Its Transmission Data
**Project Kelompok ini dibuat dalam mata kuliah Sistem Elektronika Lanjut pada Juli 2023 dengan dosen pembina Dr. Didit Widiyanto, S.Kom., M.Si.**

Berikut [Flowchart](https://drive.google.com/file/d/1lietRSVo0aO9ZDYIbinA7ShmGXW_QwrP/view?usp=sharing) dari rancangan satelit yang dibuat.

## Tujuan
 Tujuan proyek ini adalah untuk mempelajari telemetri dan komunikasi untuk menerapkan sistem sebagai dasar transmisi data satelit. Untuk menyelesaikan tugas ini, kami diharuskan menulis kode yang dapat dibaca oleh modul SIM800L dan mengirimkan respon sebagai kode balasan otomatis melalui SMS sebagai transmisi data.
## Cara Kerja
 1. Modul SIM800l digunakan sebagai modul komunikasi satelit yang dibuat dengan menggunakan provider Telkomsel
 2. Sensor DHT11 akan bekerja secara realtime untuk mendeteksi suhu sekitar
 3. Menu SMS yang dibuat adalah:
      - “hello” untuk mendapatkan informasi mengenai menu dan fitur yang tersedia
      - “rc_0” untuk mendapatkan informasi mengenai suhu dan kelembapan yang terukur
      - “rc_1” untuk mendapatkan informasi mengenai anggota kelompok proyek
 4. Satelit akan memberikan balasan yang sesuai dengan kode menu yang diberikan via SMS 

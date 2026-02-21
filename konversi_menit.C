#include <fstream>
#include <iostream>
#include <cstdio>
#include <map>
#include <tuple>
#include <ctime>

#include <TFile.h>
#include <TTree.h>

using namespace std;

// =====================================================
// KONFIGURASI MUDAH (UBAH DI SINI SAJA)
// =====================================================
const char* INPUT_DATE           = "14-01-2026";   // DD-MM-YYYY
const char* FIRST_REAL_DATA_DATE = "05-01-2026";   // padding sebelum ini
const char* INPUT_DIR            = "/home/callin/data_radioaktif/data_monitoring_asli/";
const char* OUTPUT_DIR           = "/home/callin/data_radioaktif/data_root/";

// =====================================================
// UTIL: parse DD-MM-YYYY → tm
// =====================================================
tm parse_date(const char* date)
{
    tm t = {};
    sscanf(date, "%d-%d-%d", &t.tm_mday, &t.tm_mon, &t.tm_year);
    t.tm_mon  -= 1;
    t.tm_year -= 1900;
    t.tm_hour = 0;
    t.tm_min  = 0;
    t.tm_sec  = 0;
    return t;
}

// =====================================================
// MAIN
// =====================================================
void konversi_menit()
{
    // ---------- referensi waktu global ----------
    tm t0 = {};
    t0.tm_year = 2026 - 1900;
    t0.tm_mon  = 0;
    t0.tm_mday = 1;
    time_t base_time = mktime(&t0);

    // ---------- tanggal file ----------
    tm tfile = parse_date(INPUT_DATE);
    time_t file_time = mktime(&tfile);

    // ---------- tanggal data asli pertama ----------
    tm tfirst = parse_date(FIRST_REAL_DATA_DATE);
    time_t first_real_time = mktime(&tfirst);

    long day_offset =
        difftime(file_time, base_time) / 60;

    bool is_padding_day = (file_time < first_real_time);

    // ---------- input file ----------
    char input_path[256];
    sprintf(input_path, "%s%s.txt", INPUT_DIR, INPUT_DATE);

    ifstream fin(input_path);
    map<int, tuple<int,float,float>> daily_data;

    if (!is_padding_day) {
        if (!fin.is_open()) {
            cout << "❌ Gagal membuka: " << input_path << endl;
            return;
        }

        int hh, mm, ss, cpm;
        float temp, humi;
        char comma;

        while ( fin >> hh >> comma
                   >> mm >> comma
                   >> ss >> comma
                   >> cpm >> comma
                   >> temp >> comma
                   >> humi )
        {
            int minute_of_day = hh * 60 + mm;
            daily_data[minute_of_day] = make_tuple(cpm, temp, humi);
        }
        fin.close();
    }

    // ---------- nomor file global ----------
    int file_index = tfile.tm_mday +
                     (tfile.tm_mon * 31);

    // ---------- output ROOT ----------
    char output_path[256];
    sprintf(output_path,
        "%squark_%02d-%02d-%04d_%04d.root",
        OUTPUT_DIR,
        tfile.tm_mday,
        tfile.tm_mon + 1,
        tfile.tm_year + 1900,
        file_index
    );

    TFile *f = new TFile(output_path, "RECREATE");
    TTree *t = new TTree("data", "Quark Monitoring");

    char  time_label[8];
    int   out_cpm;
    float out_temp, out_humi;

    t->Branch("time", time_label, "time/C");
    t->Branch("cpm", &out_cpm, "cpm/I");
    t->Branch("temp", &out_temp, "temp/F");
    t->Branch("humi", &out_humi, "humi/F");

    // =================================================
    // ISI DATA
    // =================================================
    if (is_padding_day) {
        // ---- 01–04 JAN → padding nol ----
        for (int m = 0; m < 1440; m++) {
            long global_time = day_offset + m + 1;
            sprintf(time_label, "%07ld", global_time);

            out_cpm = 0;
            out_temp = 0;
            out_humi = 0;

            t->Fill();
        }
    } else {
        // ---- 05 JAN dan seterusnya → data asli ----
        for (auto &it : daily_data) {
            int minute_of_day = it.first;
            tie(out_cpm, out_temp, out_humi) = it.second;

            long global_time = day_offset + minute_of_day + 1;
            sprintf(time_label, "%07ld", global_time);

            t->Fill();
        }
    }

    // ---------- simpan ----------
    t->Write();
    f->Close();
    delete f;

    cout << "✅ KONVERSI SELESAI\n";
    cout << "📄 Output: " << output_path << endl;
}

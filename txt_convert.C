#include <TFile.h>
#include <TTree.h>

#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <cstring>

using namespace std;

// ======================================================
// HITUNG DAY OFFSET
// 01-01-2026 -> 0
// ======================================================
int get_day_offset(const char* filename)
{
    const int REF_DAY = 1, REF_MONTH = 1, REF_YEAR = 2026;

    int d, m, y;
    sscanf(filename, "%d-%d-%d", &d, &m, &y);

    tm t_file = {};
    t_file.tm_mday = d;
    t_file.tm_mon  = m - 1;
    t_file.tm_year = y - 1900;

    tm t_ref = {};
    t_ref.tm_mday = REF_DAY;
    t_ref.tm_mon  = REF_MONTH - 1;
    t_ref.tm_year = REF_YEAR - 1900;

    time_t tf = mktime(&t_file);
    time_t tr = mktime(&t_ref);

    return (int)(difftime(tf, tr) / 86400);
}

// ======================================================
// MAIN
// ======================================================
void txt_convert()
{
    // ===============================
    // INPUT & OUTPUT
    // ===============================
    const char* input_txt =
        "/home/callin/data_monitoring_asli/februari/20-02-2026.txt";

    const char* output_root =
        "/home/callin/data_root/februari/quark_20-02-2026_00052.root";

    ifstream fin(input_txt);
    if (!fin.is_open()) {
        cout << "❌ Gagal membuka TXT\n";
        return;
    }

    // ===============================
    // INFO TANGGAL
    // ===============================
    const char* fname = strrchr(input_txt, '/') + 1;

    int day_offset = get_day_offset(fname);

    Int_t day, month, year;
    sscanf(fname, "%d-%d-%d", &day, &month, &year);

    // ===============================
    // ROOT FILE
    // ===============================
    TFile *outputFile = new TFile(output_root, "RECREATE");
    TTree *outputTree = new TTree("tp", "tp");

    // ===============================
    // VARIABEL TREE
    // ===============================
    Int_t hour, minute, index, cpm;
    Float_t temp, hum;

    outputTree->Branch("day",    &day,    "day/I");
    outputTree->Branch("month",  &month,  "month/I");
    outputTree->Branch("year",   &year,   "year/I");
    outputTree->Branch("hour",   &hour,   "hour/I");
    outputTree->Branch("minute", &minute, "minute/I");
    outputTree->Branch("index",  &index,  "index/I");
    outputTree->Branch("cpm",    &cpm,    "cpm/I");
    outputTree->Branch("temp",   &temp,   "temp/F");
    outputTree->Branch("hum",    &hum,    "hum/F");

    // ===============================
    // VARIABEL RAW (PARSING)
    // ===============================
    int raw_h, raw_m, raw_s, raw_cpm;
    float raw_t, raw_hum;
    string line;

    bool padded = false;

    // ===============================
    // LOOP BACA FILE (SATU LOOP SAJA)
    // ===============================
    while (getline(fin, line))
    {
        if (line.empty()) continue;

        int n = sscanf(line.c_str(),
                       "%d,%d,%d,%d,%f,%f",
                       &raw_h, &raw_m, &raw_s,
                       &raw_cpm, &raw_t, &raw_hum);

        if (n != 6) continue;

        int minute_of_day = raw_h * 60 + raw_m;

        // ===== PADDING HANYA SEKALI =====
        if (!padded) {
            for (int m = 0; m < minute_of_day; m++) {
                hour   = m / 60;
                minute = m % 60;
                index  = day_offset * 1440 + m;
                cpm = 0; temp = 0; hum = 0;
                outputTree->Fill();
            }
            padded = true;
        }

        // ===== DATA ASLI =====
        hour   = raw_h;
        minute = raw_m;
        cpm    = raw_cpm;
        temp   = raw_t;
        hum    = raw_hum;

        index = day_offset * 1440 + minute_of_day;
        outputTree->Fill();
    }

    outputFile->cd();
    outputTree->Write();
    outputFile->Close();

    cout << "✅ KONVERSI SELESAI\n";
    cout << "📅 " << day << "-" << month << "-" << year << endl;
    cout << "📏 day_offset = " << day_offset << endl;
}

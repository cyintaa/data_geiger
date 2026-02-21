void cpm_to_bq() {

    TFile *fin = TFile::Open("/home/callin/data_root/februari/quark_20-02-2026_00052.root");
    TTree *oldtree = (TTree*)fin->Get("tp");

    TFile *fout = new TFile("/home/callin/data_bq/februari/quark_20-02-2026_00052_bq.root","RECREATE");

    Int_t day, hour, minute, index;
    Int_t cpm;          // <-- FIX DI SINI (bukan Float)
    Float_t temp, hum;
    Float_t bq;

    oldtree->SetBranchAddress("day",&day);
    oldtree->SetBranchAddress("hour",&hour);
    oldtree->SetBranchAddress("minute",&minute);
    oldtree->SetBranchAddress("index",&index);
    oldtree->SetBranchAddress("cpm",&cpm);     // cocok dengan tipe asli
    oldtree->SetBranchAddress("temp",&temp);
    oldtree->SetBranchAddress("hum",&hum);

    TTree *newtree = new TTree("tp","Tree dengan Bq");

    newtree->Branch("day",&day,"day/I");
    newtree->Branch("hour",&hour,"hour/I");
    newtree->Branch("minute",&minute,"minute/I");
    newtree->Branch("index",&index,"index/I");
    newtree->Branch("cpm",&cpm,"cpm/I");
    newtree->Branch("temp",&temp,"temp/F");
    newtree->Branch("hum",&hum,"hum/F");
    newtree->Branch("bq",&bq,"bq/F");

    Long64_t nentries = oldtree->GetEntries();

    for(Long64_t i=0;i<nentries;i++){
        oldtree->GetEntry(i);

        bq = (float)cpm / 60.0f;   // <-- pastikan cast ke float

        newtree->Fill();
    }

    newtree->Write();
    fout->Close();
    fin->Close();

    printf("Selesai.\n");
}
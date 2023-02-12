#include <string>
#include <sstream>
#include <algorithm>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

//
void get_levels(TString str1, TString str2)
{
  TString filename;
  filename = TString::Format("/mnt/d/_paper_han/202303_BrKrRb/odd_A_RMF_caculations/Kr-odd/Kr81/%s/%s/level.dat",str1.Data(),str2.Data());
  cout << filename << endl;


  ifstream fi;
  fi.open(filename.Data());
  if(!fi){
    cout << "can not open " << filename << endl;
    return;
  }

  //out file
  ofstream fo_n_pos;
  fo_n_pos.open("n+.dat", ios::app);
  ofstream fo_n_neg;
  fo_n_neg.open("n-.dat", ios::app);
  ofstream fo_p_pos;
  fo_p_pos.open("p+.dat", ios::app);
  ofstream fo_p_neg;
  fo_p_neg.open("p-.dat", ios::app);

  string head;
  getline(fi, head);
  
  string line;
  TString line_new;
  Double_t beta, k;
  TString nucleon, p;
  TString orbit, ag, agp;
  Double_t F_km, ee, occ;

  // fi >> beta >> k >> nucleon >> p >> orbit >> ag >> agp >> F_km >> ee >> occ;
  // cout << beta << " " << k << " " << nucleon << " " << p << " " << orbit << " " << ag << " " << agp << " " << F_km << " " << ee << " " << occ << endl;
  // if(nucleon.CompareTo("n")==0){
  //   cout << "nucleon = " << nucleon << endl;
  // }
  // if(p.CompareTo("+")==0){
  //   cout << "p = " << p << endl;
  // }
  // TString level = orbit+ag;
  // cout << "level " << level << endl;

  stringstream ss;
  ss.str("");
  // getline(fi, line);
  // line_new = line;
  // cout << line << endl;
  // ss << line;
  // cout << ss.str() << endl;
  // ss >> beta >> k >> nucleon >> p >> orbit >> ag >> agp >> F_km >> ee >> occ;
  // cout << beta << " " << k << " " << nucleon << " " << p << " " << orbit << " " << ag << " " << agp << " " << F_km << " " << ee << " " << occ << endl;
  // getline(fi, line);
  // line_new = line;
  // cout << line << endl;

  bool b_n_pos = 0;
  bool b_n_neg = 0;
  bool b_p_pos = 0;
  bool b_p_neg = 0;

  bool b_level = 0;

  while(1){
    ss.clear();
    ss.str("");

    b_n_pos = 0;
    b_n_neg = 0;
    b_p_pos = 0;
    b_p_neg = 0;
    b_level = 0;

    //
    getline(fi, line);
    if(!fi.good()) break;

    line_new = line;
    // cout << line << endl;
    if(line_new.Contains("h11/2") || line_new.Contains("i13/2")){
      continue;
    }
    ss << line;
    // cout << ss.str() << endl;
    ss >> beta >> k >> nucleon >> p >> orbit >> ag >> agp >> F_km >> ee >> occ;
    // cout << beta << " " << k << " " << nucleon << " " << p << " " << orbit << " " << ag << " " << agp << " " << F_km << " " << ee << " " << occ << endl;

    if(nucleon.CompareTo("n")==0 && p.CompareTo("+")==0){
      b_n_pos = 1;
    }
    if(nucleon.CompareTo("n")==0 && p.CompareTo("-")==0){
      b_n_neg = 1;
    }
    if(nucleon.CompareTo("p")==0 && p.CompareTo("+")==0){
      b_p_pos = 1;
    }
    if(nucleon.CompareTo("p")==0 && p.CompareTo("-")==0){
      b_p_neg = 1;
    }
    TString level = orbit+ag;
    if(level.CompareTo("1g9/2")==0 || level.CompareTo("1f7/2")==0 || level.CompareTo("2p3/2")==0 || level.CompareTo("1f5/2")==0 || level.CompareTo("2p1/2")==0){
      b_level = 1;
    }

    // n_pos
    if(b_n_pos && b_level){
      fo_n_pos << beta << " " << level << " " << agp << " " << ee << endl;
    }
    // n_neg
    if(b_n_neg && b_level){
      fo_n_neg << beta << " " << level << " " << agp << " " << ee << endl;
    }

    // p_pos
    if(b_p_pos && b_level){
      fo_p_pos << beta << " " << level << " " << agp << " " << ee << endl;
    }
    // p_neg
    if(b_p_neg && b_level){
      fo_p_neg << beta << " " << level << " " << agp << " " << ee << endl;
    }
  }

  fo_n_pos.close();
  fo_n_neg.close();
  fo_p_pos.close();
  fo_p_neg.close();

  fi.close();
}

//
void get_level_result()
{
  ifstream fi;
  fi.open("beta.dat");
  if(!fi){
    cout << "can not open beta.dat" << endl;
    return;
  }

  TString str1, str2;
  while(1){
    fi >> str1 >> str2;
    if(!fi.good()) break;

    cout << str1 << " " << str2 << endl;

    get_levels(str1, str2);
  }
}
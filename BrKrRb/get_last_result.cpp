#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void get_folder_vector(TString path, vector<TString> &v_f);


//
void get_last_result(TString str1, Int_t num, TString str2)
{
  TString filename = TString::Format("/mnt/c/Users/hanX/Desktop/paper2/odd_A_RMF_caculations/%s-odd/%s%d/%s/",str1.Data(),str1.Data(),num,str2.Data());
  cout << filename.Data() << endl;

  vector<TString> v_folder;
  get_folder_vector(filename, v_folder);

  // for(int i=0;i<v_folder.size();i++){
  //   cout << v_folder[i] << endl;
  // }
  if(v_folder.size()==0){
    cout << "no caculation file" << endl;
    return; 
  }

  ofstream fo;
  fo.open(TString::Format("%sresult.txt",filename.Data()));
  if(!fo){
    cout << "cannot open " << TString::Format("%sout.txt",filename.Data()) << endl;
    return;
  }
  fo << "beta    gamma    total_energy" << endl; 

  //loop
  for(int i=0;i<v_folder.size();i++){
    ifstream fi;
    fi.open(TString::Format("%s/dic.out",v_folder[i].Data()).Data());
    if(!fi){
      cout << "can not open " << TString::Format("%s/dic.out",v_folder[0].Data()).Data() << endl;
      return;
    }

    string line;
    vector<TString> v_lines;
    while(1){
      getline(fi, line);
      if(!fi.good()) break;

      v_lines.push_back(line);
    }
    fi.close();

    TString s_gamma;
    TString s_beta;
    TString s_total_energy;
    bool flag_gamma = 0;
    bool flag_beta = 0;
    bool flag_total_energy = 0;
    int a, b;

    TString gamma, beta, total_energy;

    for(int j=v_lines.size();j>0;j--){
      if(flag_gamma && flag_beta && flag_total_energy) break;

      TString s_gamma(v_lines[j-1](0,6));
      TString s_beta(v_lines[j-1](0,6));
      TString s_total_energy(v_lines[j-1](0,13));

      if(!flag_gamma && s_gamma.CompareTo(" gamma") == 0){
        // cout << v_lines[j-1] << endl;
        a = v_lines[j-1].Last(' ');
        b = v_lines[j-1].Length();
        // cout << a << " " << b << endl;
        // cout << v_lines[j-1](a+1,b) << endl;
        gamma = v_lines[j-1](a+1,b);

        flag_gamma = 1;
      }

      if(!flag_beta && s_beta.CompareTo(" beta0") == 0){
        // cout << v_lines[j-1] << endl;
        a = v_lines[j-1].Last(' ');
        b = v_lines[j-1].Length();
        // cout << a << " " << b << endl;
        // cout << v_lines[j-1](a+1,b) << endl;
        beta = v_lines[j-1](a+1,b);

        flag_beta = 1;
      }

      if(!flag_total_energy && s_total_energy.CompareTo(" Total Energy") == 0){
        // cout << v_lines[j-1] << endl;
        a = v_lines[j-1].Last(' ');
        b = v_lines[j-1].Length();
        // cout << a << " " << b << endl;
        // cout << v_lines[j-1](a+1,b) << endl;
        total_energy = v_lines[j-1](a+1,b);

        flag_total_energy = 1;
      }
    }

    fo << beta << "    " << gamma << "    " << total_energy << endl;
  }

  fo.close();
}

//
void get_folder_vector(TString path, vector<TString> &v_f)
{
  struct stat stat_buf;

  DIR *dir;
  struct dirent *p;
  if(!(dir = opendir(path.Data()))){
    cout << "folder does not exsit" << endl;
    return;
  }

  while((p = readdir(dir)) != 0){
    if(strcmp(p->d_name,".")!=0 && strcmp(p->d_name,"..")!=0){
      // cout << p->d_name << endl;
      int ret = stat(TString::Format("%s%s",path.Data(),p->d_name).Data(), &stat_buf);
      if (ret < 0){
        perror("stat error");
        return;
      }

      if (S_ISREG(stat_buf.st_mode)) {
        // printf("%s: general file\n", p->d_name);
        continue;
      }
      else if(S_ISDIR(stat_buf.st_mode)) {
        // printf("%s: direcotry\n", p->d_name);
        v_f.push_back(TString::Format("%s%s",path.Data(),p->d_name));
      }
      else {
        // printf("%s: other file type\n", p->d_name);
        continue;
      }
    }
  }

  return;
}
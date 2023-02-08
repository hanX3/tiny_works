#include <algorithm>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void get_folder_vector(TString path, vector<TString> &v_f);

//
void get_min_total_energy(TString str, Int_t num)
{
  TString filename = TString::Format("/mnt/c/Users/hanX/Desktop/paper2/odd_A_RMF_caculations/%s-odd/%s%d/",str.Data(),str.Data(),num);
  cout << filename.Data() << endl;

  vector<TString> v_folder;
  get_folder_vector(filename, v_folder);

  for(int i=0;i<v_folder.size();i++){
    cout << v_folder[i] << endl;
  }

  //loop
  for(int i=0;i<v_folder.size();i++){
    ifstream fi;
    fi.open(TString::Format("%s/result.txt",v_folder[i].Data()).Data());
    if(!fi){
      cout << "can not open " << TString::Format("%s/result.txt",v_folder[i].Data()).Data() << endl;
      continue;
    }

    string line;
    getline(fi, line);

    vector<double> v_beta;
    vector<double> v_gamma;
    vector<double> v_energy;

    double beta, gamma, energy, beta_2;
    while(1){
      fi >> beta >> gamma >> energy;
      if(!fi.good()) break;
      v_beta.push_back(beta);
      v_gamma.push_back(gamma);
      v_energy.push_back(energy);
    }
    fi.close();

    int min_index = std::min_element(v_energy.begin(),v_energy.end())-v_energy.begin();
    // cout << "min_index " << min_index << endl;

    cout << "beta " << v_beta[min_index] << "  gamma " << v_gamma[min_index] << "  energy " << v_energy[min_index] << "  ";
    int a = v_folder[i].Last('/');
    int b = v_folder[i].Length();
    cout << "folder " << str << num << "/" << v_folder[i](a+1,b) << "/" << v_beta[min_index] << endl;
  }

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
// get beta.dat file
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void get_folder_vector(TString path, vector<TString> &v_f);

//
void get_beta()
{
  TString filename = TString::Format("/mnt/d/_paper_han/202303_BrKrRb/odd_A_RMF_caculations/Kr-odd/Kr81");
  cout << filename.Data() << endl;

  vector<TString> v_folder;
  get_folder_vector(TString::Format("%s/A-han/", filename.Data()), v_folder);
  get_folder_vector(TString::Format("%s/B/", filename.Data()), v_folder);
  get_folder_vector(TString::Format("%s/C/", filename.Data()), v_folder);
  get_folder_vector(TString::Format("%s/D/", filename.Data()), v_folder);
  get_folder_vector(TString::Format("%s/E/", filename.Data()), v_folder);
  get_folder_vector(TString::Format("%s/F-A/", filename.Data()), v_folder);
  get_folder_vector(TString::Format("%s/G-A/", filename.Data()), v_folder);
  get_folder_vector(TString::Format("%s/H-B/", filename.Data()), v_folder);
  
  //
  for(int i=0;i<v_folder.size();i++){
    cout << v_folder[i] << endl;
  }

  ofstream fo;
  fo.open("beta.dat");
  if(!fo){
    cout << "can not open " << "file" << endl;
    return;
  }

  for(int i=0;i<v_folder.size();i++){

    int a = v_folder[i].Last('/');
    int b = v_folder[i].Length();
    // cout << a << endl;
    // cout << b << endl;

    TString sub = v_folder[i](0,a);
    int c = sub.Last('/');
    // cout << sub << endl;
    // cout << sub(c+1,a) << endl;
    // cout << v_folder[i](a+1,b) << endl;

    fo << sub(c+1,a) << " " << v_folder[i](a+1,b) << endl;
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

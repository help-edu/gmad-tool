#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

static string gmad_path;

inline string getFileName(string _path)
{
	for(size_t i = _path.length()-1; i > 1; i--)
		if(_path.at(i) == '\\')
			return _path.substr(i + 1, _path.length() - 1);

	return string();
}

inline string getPath(string _path)
{
	// find pos of /
	for(size_t i = _path.length()-1; i > 1; i--)
		if(_path.at(i) == '\\')
			return _path.substr(0, i+1);
	
	return string();
}

inline string getExt(string filename)
{
	for(size_t i = filename.length() - 1; i > 1; i--)
		if(filename.at(i) == '.')
			return filename.substr(i, filename.length() - 1);
	
	return string();	
}

inline string getNoExt(string filename)
{
	for(size_t i = filename.length() - 1; i > 1; i--)
		if(filename.at(i) == '.')
			return filename.substr(0, i);
	
	return string();	
}

inline void extract_obj(string dest, string filepath)
{
	if( getExt(filepath) == ".gma")
	{
		cout << getFileName(filepath);
		
		string command = gmad_path + string(" extract -file \"");
			command.append(filepath);
			command.append("\" -out \"");
			command.append(dest + string("Production\\") + getNoExt(filepath));
			command.append("\" >NUL");
		
		unsigned t0 = clock();
		int ret = system(command.c_str());
		
		cout << " " << float(clock() - t0) / CLOCKS_PER_SEC << "s."; 
		
		if(!ret)
			cout << " (OK.)";
		else
			cout << " (NO~)";
			
		cout << endl;
	}
}

int main(int argc, char *argv[])
{		
	string _here = getPath(string(argv[0]));

	if(const char* env_p = std::getenv("GMAD_PATH"))
        gmad_path = string(env_p);
    else {
    	cout << "Info: you can specify GMAD_PATH to your gmad.exe in os environment\n";
		gmad_path = string("gmad.exe");
	}	
	
	if(argc < 2) {
		cout << "\n\nUsage: Drag and drop multiple *.gma files\n";
	} else
	
		for(size_t i = 1; i < argc; i++) {
			cout << "[" << i << "/" << argc - 1 << "] ";
			extract_obj(_here, string(argv[i]));
		}

    return EXIT_SUCCESS;
}

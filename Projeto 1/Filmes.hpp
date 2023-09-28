#include<vector>
#include<string>

using namespace std;

class filmesCrop{
    private:
        string tconst;
        string titleType;
        string primaryType;
        string originalTitle;
        unsigned isAdult;
        int startYear;
        int endYear;
        int runtimeMinutes;
        vector<string> genres;
        vector<string> cinema_id;
};

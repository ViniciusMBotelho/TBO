#include<vector>
#include<string>

using namespace std;

class Filme{
    private:
        int tconst;
        string titleType;
        string primaryTitle;
        string originalTitle;
        int isAdult;
        int startYear;
        int endYear;
        int runtimeMinutes;
        int hash;
        vector<string> genres;
        vector<string> cinema_id;

    public:
        int getTconst()
        {
            return tconst;
        }

        void setTconst(int tconstA)
        {
            tconst = tconstA;
        }

        string getTitleType()
        {
            return titleType;
        }

        void setTitleType(string titleTypeA)
        {
            titleType = titleTypeA;
        }

        string getPrimaryTitle()
        {
            return primaryTitle;
        }

        void setPrimaryTitle(string primaryTitleA)
        {
            primaryTitle = primaryTitleA;
        }

        string getOriginalTitle()
        {
            return originalTitle;
        }

        void setOriginalTitle(string originalTitleA)
        {
            originalTitle = originalTitleA;
        }

        unsigned getIsAdult()
        {
            return isAdult;
        }

        void setIsAdult(unsigned isAdultA)
        {
            isAdult = isAdultA;
        }

        int getStartYear()
        {
            return startYear;
        }

        void setStartYear(int startYearA)
        {
            startYear = startYearA;
        }

        int getEndYear()
        {
            return endYear;
        }

        void setEndYear(int endYearA)
        {
            endYear = endYearA;
        }

        int getRuntimeMinutes()
        {
            return runtimeMinutes;
        }

        void setRuntimeMinutes(int runtimeMinutesA)
        {
            runtimeMinutes = runtimeMinutesA;
        }

        vector<string> getGenres()
        {
            return genres;
        }

        void setGenres(string generoA)
        {
            genres.push_back(generoA);
        }

        vector<string> getCinema_id()
        {
            return cinema_id;
        }

        void setCinema_id(string cinema_idA)
        {
            cinema_id.push_back(cinema_idA);
        }

        int getHash()
        {
            return hash;
        }

        void setHash(int hashA)
        {
            hash = hashA%100;
        }
};

#ifndef JEU
#define JEU

#endif // JEU

class Jeu
{



public:
    bool online;
    int phase;
    int selfLife;
    int foeLife;




    void piocher(int n);
    void poser(int main_x, int terrain_x, bool def);
    void poser(int sac_x,int main_x,int terrain_x, bool def);
    void poser(int sac1_x, int sac2_x, int main_x, int terrain_x,bool def);
    void attaquer(int moi_x, int adversaire_x=-1);
    //void switch_position(int terrain_x);
    void phase_suivante();
    void
};

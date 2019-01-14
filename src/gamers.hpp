
class gamer1{

public:
    gamer1()
    {};
    
    gamer1(double x, double y, double z)
    : m_x(x), m_y(y), m_z(z){};
      /* iscrtavanje crvenog igraca */
    void gamer1_draw(void);
      /* zeleno crveni pravougaonik koji pokazuje koliko je helta ostalo igracu pre prekida igrice */
    void health();
      /* merac brzine metka koji se ispaljuje  */
    double speed(double up_vector_y_cor);
     /* pomoc da igrac dobije drugu sansu napuni helt na pocetni kao sa pocetka igrice */    
    void help(double m_x);
    
    double m_x;
    double m_y, m_y2 = 0;
    double m_z;
    double m_rot = 0;
    double m_health_red  = 0;
    int red_up = 1;
};



/******************
    PLAVI IGRAC
 ******************/

class gamer2{

public:
    gamer2()
    {};
    
    gamer2(double x, double y, double z)
    : m_x(x), m_y(y), m_z(z){};
    
      /* iscrtavanje plavog igraca */
    void gamer2_draw(void);
      /* zeleno crveni pravougaonik koji pokazuje koliko je helta ostalo igracu pre prekida igrice */
    void health();
      /* merac brzine metka koji se ispaljuje  */      
    double speed(double up_vector_y_cor);
     /* pomoc da igrac dobije drugu sansu napuni helt na pocetni kao sa pocetka igrice */
    void help(double m_x);
    
    double m_x;
    double m_y, m_y2 = 0;
    double m_z;
    double m_rot = 0;
    double m_health_blue = 0;
    int blue_up = 1;
};

class fire_red{
  
public:
  fire_red()
  {}
  
   fire_red(double x, double y, double z, int fire_r)
   :m_x(x), m_y(y), m_z(z), fire_r(fire_r){};
   
   /* 'metak' koji ispaljuje crveni igrac */
   void fire(double m_x, double m_y, double m_z);
      
  double m_x;
  double m_y;
  double m_z;
  int fire_r = 0;
  double fire_rot;
  double fire_speed;
};

class fire_blue{
  
public:
  fire_blue()
  {}
  
   fire_blue(double x, double y, double z, int fire_b)
   :m_x(x), m_y(y), m_z(z), fire_b(fire_b){};
   
   /* 'metak' koji ispaljuje plavi igrac */   
   void fire(double m_x, double m_y, double m_z);
      
  double m_x;
  double m_y;
  double m_z;
  int fire_b = 0;
  double fire_rot;
  double fire_speed;
};
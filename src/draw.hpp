
class floor_tank{
public:
    floor_tank(double x, double y, double z)
    : m_x(x), m_y(y), m_z(z)
    {};
    /* iscrtavanje podloge po kojoj se krecu tenkovi */
    void floor_draw();
    
private:
  
  double m_x;
  double m_y;
  double m_z;
  
};


/* sivi zid koji se krece po y osi */
class obstacle{
public:
  obstacle()
  {}
  
  obstacle(double x, double y, double z)
  :m_x(x), m_y(y), m_z(z)
  {}
  
/* iscrtavanje zida i njegovo pomeranje gore-dole */
  double obstacle_draw(double up_vector_y_cor);
  
  double m_x;
  double m_y;
  double m_z;
  int up = 1;

};

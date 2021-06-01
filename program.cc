#include "Player.hh"
#include <climits>

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Xicote


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
  
  map<int, stack<Pos> > tresor; // Mapa que conté la id de un nan i el camí que ha de recorrer per anar al tresor més proper
  
  
  
  typedef vector<int> VI;
  typedef vector<vector<bool> > MB;
  typedef vector<vector<Pos> > M;
  typedef vector<vector<int> > MID;
  typedef pair<double, Pos> Arc;
  
  void moure(int nan, Pos direccio){
      Pos centre = unit(nan).pos;
      int i = direccio.i - centre.i;
      int j = direccio.j - centre.j;
      
        if( i < 0 and j > 0) // Ens movem cap a dalt a la dreta
          command(nan, RT);
      
          else if( i < 0 and j < 0) // Ens movem cap a dalt a la esquerra
            command(nan, TL);
       
        else if( i > 0 and j < 0) // Ens movem cap a baix a la esquerra
            command(nan, LB);
        
        else if( i > 0 and j > 0) // Ens movem cap a baix a la dreta
            command(nan, BR);
            
        else if(i < 0 and j == 0) // Ens movem cap a dalt
            command(nan, Top);
        
        else if(i > 0 and j == 0) // Ens movem cap a baix
            command(nan, Bottom);
        
        else if( i == 0 and j < 0) // Ens movem cap a la esquerra
            command(nan, Left);
        
        else if( i == 0 and j > 0) // Ens movem cap a la dreta
            command(nan, Right);
  
  }
 
 /* Funcions per trobar tresors */
 
  Pos tresorproper(int id ){
        vector<vector<double> > dist(60, vector<double>(60, INT_MAX)); dist[unit(id).pos.i][unit(id).pos.j] = 0;
        vector<vector<Pos> > previ(60, vector<Pos> (60));
        vector <vector <bool> > S(60, vector<bool>(60, false));
        
        priority_queue<Arc, vector<Arc>, greater<Arc> > Q;
        Pos inici  (unit(id).pos.i, unit(id).pos.j);
        
        Q.push(Arc(0, inici));
        
        bool found= false;
        Pos tresor;
        
        while(not Q.empty() and not found){
            Pos u = Q.top().second; Q.pop();
            if (not S[u.i][u.j]){
                S[u.i][u.j] = true;
                for(int i = 0; i < 8 and not found; ++i){
                    Pos v = u + Dir(i);
                    
                    if(pos_ok(v)){
                        if(cell(v).treasure){
                            found = true;
                            tresor = v;
                        }
                       if(cell(v).type != Abyss and cell(v).type != Granite){
                        double c = (cell(v).type == Rock) ? 5 : 1;
                            if(dist[v.i][v.j] > dist[u.i][u.j] + c ){
                                dist[v.i][v.j] = dist[u.i][u.j] + c;
                                previ[v.i][v.j] = u;
                                Q.push(Arc(dist[v.i][v.j], v));

                            }
                    }
                }
            }
        }
    }
        
        bool primer = false;
        
        while(not primer){
            
            if(previ[tresor.i][tresor.j] == inici)
                primer = true;
            else
                tresor = previ[tresor.i][tresor.j];
        }
        
        return tresor;
            
  }
        
  
  
  void busca_tresor(int nanid){
      Pos tre = tresorproper(nanid);
      moure(nanid, tre);
  }
  /* Funcions per trobar tresors */      
        
        
       
  
  

 /* Funcions per trobar el balrog */        

                
  
 pair<Pos, double> buscaenemycell(int id){
     
     
     
      vector<vector<double> > dist(60, vector<double>(60, INT_MAX)); dist[unit(id).pos.i][unit(id).pos.j] = 0;
        vector<vector<Pos> > previ(60, vector<Pos> (60));
        vector <vector <bool> > S(60, vector<bool>(60, false));
        
        priority_queue<Arc, vector<Arc>, greater<Arc> > Q;
        Pos inici  (unit(id).pos.i, unit(id).pos.j);
        
        Q.push(Arc(0, inici));
        
        bool found= false;
        Pos tresor;
        
        while(not Q.empty() and not found){
            Pos u = Q.top().second; Q.pop();
            if (not S[u.i][u.j]){
                S[u.i][u.j] = true;
                
                for(int i = 0; i < 8 and not found; ++i){
                    Pos v = u + Dir(i);
                    
                    if(pos_ok(v)){
                        if(cell(v).id == -1 and cell(v).owner != me() and cell(v).owner != -1 and cell(v).type != Abyss and cell(v).type != Outside and cell(v).type != Granite){
                            found = true;
                            tresor = v;
                        }
                       if(cell(v).type != Abyss and cell(v).type != Granite){
                        double c = (cell(v).type == Rock) ? 5 : 1;
                            if(dist[v.i][v.j] > dist[u.i][u.j] + c ){
                                dist[v.i][v.j] = dist[u.i][u.j] + c;
                                previ[v.i][v.j] = u;
                                Q.push(Arc(dist[v.i][v.j], v));

                            }
                    }
                }
                }
            }
        }
        double distancia = dist[tresor.i][tresor.j];
        
        bool primer = false;
        
        while(not primer){
            

            if(previ[tresor.i][tresor.j] == inici)
                primer = true;
            else
                tresor = previ[tresor.i][tresor.j];
        }
        
        return make_pair(tresor, distancia);
            
 }
  
  pair<Pos, double> buscaemptycell(int id){
      vector<vector<double> > dist(60, vector<double>(60, INT_MAX)); dist[unit(id).pos.i][unit(id).pos.j] = 0;
        vector<vector<Pos> > previ(60, vector<Pos> (60));
        vector <vector <bool> > S(60, vector<bool>(60, false));
        
        priority_queue<Arc, vector<Arc>, greater<Arc> > Q;
        Pos inici  (unit(id).pos.i, unit(id).pos.j);
        
        Q.push(Arc(0, inici));
        
        bool found= false;
        Pos tresor;
        
        while(not Q.empty() and not found){
            Pos u = Q.top().second; Q.pop();
            if (not S[u.i][u.j]){
                S[u.i][u.j] = true;
                
                for(int i = 0; i < 8 and not found; ++i){
                    Pos v = u + Dir(i);
                    
                    if(pos_ok(v)){
                        if(cell(v).id == -1 and cell(v).owner == -1 and cell(v).type != Abyss and cell(v).type != Outside and cell(v).type != Granite){
                            found = true;
                            tresor = v;
                        }
                       if(cell(v).type != Abyss and cell(v).type != Granite){
                        double c = (cell(v).type == Rock) ? 5 : 1;
                            if(dist[v.i][v.j] > dist[u.i][u.j] + c ){
                                dist[v.i][v.j] = dist[u.i][u.j] + c;
                                previ[v.i][v.j] = u;
                                Q.push(Arc(dist[v.i][v.j], v));

                            }
                    }
                }
                }
            }
        }
        double distancia = dist[tresor.i][tresor.j];
        
        bool primer = false;
        
        while(not primer){
            

            if(previ[tresor.i][tresor.j] == inici)
                primer = true;
            else
                tresor = previ[tresor.i][tresor.j];
        }
        
        return make_pair(tresor, distancia);
            
 }
  
 
  
 
   Pos nanproper(int id ){
        vector<vector<double> > dist(60, vector<double>(60, INT_MAX)); dist[unit(id).pos.i][unit(id).pos.j] = 0;
        vector<vector<Pos> > previ(60, vector<Pos> (60));
        vector <vector <bool> > S(60, vector<bool>(60, false));
        
        priority_queue<Arc, vector<Arc>, greater<Arc> > Q;
        Pos inici  (unit(id).pos.i, unit(id).pos.j);
        
        Q.push(Arc(0, inici));
        
        bool found= false;
        Pos tresor;
        
        while(not Q.empty() and not found){
            Pos u = Q.top().second; Q.pop();
            if (not S[u.i][u.j]){
                S[u.i][u.j] = true;
                for(int i = 0; i < 8 and not found; ++i){
                    if(Dir(i) == Top or Dir(i) == Bottom or Dir(i) == Left or Dir(i) == Right){
                    Pos v = u + Dir(i);
                    
                    if(pos_ok(v)){
                        if(cell(v).id != -1 and unit(cell(v).id).type == Dwarf and unit(cell(v).id).player == me()){
                            found = true;
                            tresor = v;
                        }
                       if(cell(v).type != Abyss and cell(v).type != Granite){
                        double c = (cell(v).type == Rock) ? 5 : 1;
                            if(dist[v.i][v.j] > dist[u.i][u.j] + c ){
                                dist[v.i][v.j] = dist[u.i][u.j] + c;
                                previ[v.i][v.j] = u;
                                Q.push(Arc(dist[v.i][v.j], v));

                            }
                    }
                }
                }
            }
        }
    }
        
        bool primer = false;
        
        while(not primer){
            
            if(previ[tresor.i][tresor.j] == inici)
                primer = true;
            else
                tresor = previ[tresor.i][tresor.j];
        }
        
        return tresor;
            
  }
  
  
    void buscanan(int magid){
        Pos nan = nanproper(magid);
        moure(magid, nan);
    }
  
  void move_dwarves(){
      VI D = dwarves(me());
      int n = D.size();
      for (int i = 0; i < n; ++i){ // Tractem cada nan
          int id = D[i];
           Pos centre = (unit(id).pos);
          if (round() <= 150){
            for(int i = 0; i < 8 ; ++i){
                if(pos_ok(centre + Dir(i)) and cell(centre  + Dir(i)).id != -1 ){
                    if(unit(cell(centre + Dir(i)).id).type == Dwarf and unit(cell(centre + Dir(i)).id).player != me()){
                        moure(id , (centre + Dir(i)));
                    }
            
                }
            }
      
            busca_tresor(id);
              
      }
      else{
              for(int i = 0; i < 8 ; ++i){
                if(pos_ok(centre + Dir(i)) and cell(centre  + Dir(i)).id != -1 ){
                    if(unit(cell(centre + Dir(i)).id).type == Dwarf and unit(cell(centre + Dir(i)).id).player != me()){
                        moure(id , (centre + Dir(i)));
                    }

            
                }
            }
      
          pair<Pos, double> enem =  buscaenemycell(id);
          pair<Pos, double> empt = buscaemptycell(id);
          if(empt.second >= enem.second) 
              moure(id, enem.first);
          else
              moure(id, empt.first);
      }
      }
  }
  
  
  
  void move_wizards(){
       VI W = wizards(me());
      int n = W.size();
      for(int i = 0; i < n; ++i){
          int id = W[i];
              buscanan(id);
  
  }
  }
  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
      move_dwarves();
      move_wizards();
      
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);


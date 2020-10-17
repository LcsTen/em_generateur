#ifndef tile_h
#define tile_h

class Tile{
	private:
		int temperature;
		int humidity;
		int nutrients;
		int elevation;
		
	public:
		Tile();
		Tile(int temp,int hum,int nut,int elev);
		
		int getTemp() const;
		int getHum() const;
		int getNut() const;
		int getElev() const;
};

#endif // tile_h

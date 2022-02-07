//Justin McKnight CS302 2/7/22
//Lab 1 Music 
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <typeinfo>
#include <vector>

using namespace std;

//Song Class that hold song information
class Song{
	public:
		string title;
		int time;
		int track;
};
//Album Class that holds songs and keeps track of total time
class Album{
	public:
		map<int, Song *> songs;
		string name;
		int time;
};
//Artist class that holds albums and keeps track of total time and number of songs
class Artist{
	public:
		map<string, Album *> albums;
		string name;
		int time;
		int nsongs;
};
//converts all '_' characters into spaces in given string.
void underscoreToSpace(string &text){
	for(size_t i = 0; i<text.size(); i++){
		if(text[i] == '_') text[i] = ' ';
	}
}
/*Program takes name of file on command line argument and reads in data of format
 * Title Time(m:s) Artist Album Genre Track and prints out data sorted
 * lexicographically in a specified format
 */
int main(int argc, char** argv) {
	string filename,title, name, albumName, genre, timeString, seconds;
	int track, time,m,s,size, albumSize;
	ifstream file;
	Song* song;
	Album* album;
	Artist* artist;
	map<string, Artist *> artists;

//Opens the file and error checks
	if(argc > 2) return 0;
	filename = argv[1];
	file.open(filename.c_str());
	if(!(file.is_open())){
		return 0;
	}
/*Loop through each line in the file creating a new Song for each, and if it does not
 * exist, creates a new Album and Artist for the song. Also removes '_' characters from strings
 * and converts time into a usable format.
 * Program then prints each artist, their albums, and each albums songs sorted lexicographically and 
 * numerically
*/
  while(true){
		song = new Song;
		album = new Album;
		artist = new Artist;
//Reads in a whole line from the file into different usable variables
		file >> title >> timeString >>name >> albumName >> genre >> track;
//Deletes new pointers if at end of file
		if(file.eof()){
			delete song;
			delete album;
			delete artist;
			break;
		}
//Converts given time into total amount of seconds using sscanf and removes '_' characters
		time = sscanf(timeString.c_str(), "%d:%d", &m, &s);
		time = m*60 + s;
		underscoreToSpace(title);
		underscoreToSpace(name);
		underscoreToSpace(albumName);

//Inputs data into each instance of the new class and inserts into maps
		song->title= title;
		song->time=time;
		song->track = track;
		if(artists.find(name) == artists.end()){
			artist->name = name;
			artist->nsongs = 0;
			artist->time = 0;
			artists.insert(make_pair(name, artist));
		}else{
			delete artist;
		}
		if(artists[name]->albums.find(albumName) == artists[name]->albums.end()){
			album->name = albumName;
			album->time = 0;
		}else{
			delete album;
		}
		artists[name]->albums.insert(make_pair(albumName, album));
		artists[name]->albums[albumName]->songs.insert(make_pair(track, song));
//Updates time and nsongs variables for the album and artist
		artists[name]->albums[albumName]->time += time;
		artists[name]->time += time;
		artists[name]->nsongs++;
	}
	file.close();
/*Converts the time back into the original format and iterates through maps to print out required information
 * then deletes pointers after use
 */
	for(map<string, Artist* >::iterator mit = artists.begin(); mit!=artists.end(); mit++){
		m = mit->second->time/60;
		s = mit->second->time%60;
		printf("%s: %d, %d:%02d\n", mit->first.c_str(), mit->second->nsongs, m, s);
		for(map<string, Album* >::iterator nit = mit->second->albums.begin(); nit!= mit->second->albums.end(); nit++){
			size = nit->first.length()+8;
			albumSize = nit->second->songs.size();
			m = nit->second->time/60;
			s = nit->second->time%60;
			printf("%*s: %d, %d:%02d\n", size, nit->first.c_str(), albumSize, m, s );
			for(map<int, Song* >::iterator sit = nit->second->songs.begin(); sit!= nit->second->songs.end(); sit++){
				m = sit->second->time/60;
				s = sit->second->time%60;
				printf("%*s%d. %s: %d:%02d\n", 16, "", sit->first, sit->second->title.c_str(), m, s); 
				delete sit->second;
			}
			delete nit->second;
		}
		delete mit->second;

	}
	


	return 0;
}

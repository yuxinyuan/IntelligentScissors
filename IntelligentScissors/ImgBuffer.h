#ifndef _IMGBUFFER_H_
#define _IMGBUFFER_H_

#include <list>
#include <tuple>
#include "fibheap.h"

struct Point {
	int _x, _y;
	Point() : _x(0), _y(0) {}
	Point(int x, int y) : _x(x), _y(y) {}
};

enum class nodePathStatus {
	INACTIVE,
	INITIAL,
	ACTIVE,
	EXPANDED
};

enum class seedSelectStatus {
	SELECTED,
	MANUALSEED,
	AUTOSEED
};

struct Seed {
	Point coord;
	seedSelectStatus seedStatus;
	Seed() : coord(0, 0), seedStatus(seedSelectStatus::SELECTED) {}
	Seed(int x, int y, seedSelectStatus status = seedSelectStatus::SELECTED) :
		coord(x, y), seedStatus(status)
	{}
};

// subclass FibHeapNode in order to use fibheap
struct Node : public FibHeapNode {
	double totalCost;
	double linkCost[8];
	nodePathStatus pathStatus;
	Node* prevNode;
	int _x, _y;
	Node() : FibHeapNode(), prevNode(nullptr) {}
	~Node();
	Node& operator=(Node& other);
	bool operator==(Node& other);
	bool operator<(Node& other);
};

typedef std::tuple<unsigned char, unsigned char, unsigned char> RGBTuple;

class ImgBuffer
{
public:
	ImgBuffer();
	~ImgBuffer();
public:
	void cleanBuffer();						// clean the image buffer, delete all pixel arrays and node buffer
	void loadImage(const char* filename);	// load filename into the current buffer, may want to call cleanBuffer() first
	unsigned char* generatePixelNode();		// generate a pixel node array from nodeBuffer
	unsigned char* generateCostGraph();		// generate a cost graph array from nodeBuffer
	void liveWireDP(Point seed);			// perform live DP with given seed seed on nodeBuffer
	void recordLastWire(Point pos);			// record the new wire from the new seed pos to last seed, mark pixels on the wire

	RGBTuple getOriginalPixel(Point pos);	// get the RGB value of the original image at given location
	RGBTuple getOriginalPixel(int x, int y);
public:
	int _imgWidth, _imgHeight, padWidth;
	unsigned char* originalPixelArray;
	unsigned char* contourPixelArray;
	Node* nodeBuffer;
	Point firstSeed, activeSeed;
	std::list<Seed> selectedNodes;
};

#endif // !_IMGBUFFER_H_



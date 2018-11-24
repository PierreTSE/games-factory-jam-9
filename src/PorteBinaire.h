#pragma once

struct PorteBinaire
{
public:
	void ChangementEtat() { ouvert = !ouvert; };

	int x, y;
	bool ouvert;

};
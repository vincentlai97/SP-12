#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <string>

void chooseShip(int shipNum)
{
	char ship1[5][20] =
	{
		"__",
		"| \\",
		"=[_H)--.____",
		"=[+-,------'",
		" [_/"
	}; 
	char ship2[5][20] = 
	{
		"     /\\",
		" |\\  \\ \\",
		"| <====}>",
		" |/  / /",
		"     \\/"
	};

	switch (shipNum)
	{
	case 1:
		for (int count = 0; count < 5; count++)
		{
			strcpy(ship[count], ship1[count]);
		}
		break;
	case 2:
		for (int count = 0; count < 5; count++)
		{
			strcpy(ship[count], ship2[count]);
		}
		break;
	}
}

class Scoreboard
{
	public:
		void addPlayer(std::string playernName, int points) 
		{
			std::string playerName; 
			Entry e;
			e.name = playerName;
			e.score = points;
			m_scoreboard.push_back(e);
		}

		void Print () 
		{
			for (int i = 0; i < m_scoreboard.size(); ++i)
			{
				std::cout << (i + 1) << ":\t" << m_scoreboard[i].name << "\t" << m_scoreboard[i].score << "\n";
			}
		}

		void RemovePlayer(std::string nameToRemove)
		{
			for (std::vector<Entry>::iterator i = m_scoreboard.begin(); i != m_scoreboard.end(); ++i)
			{
				if (i->name == nameToRemove)
				{
					m_scoreboard.erase(i);
					break;
				}
			}
		}

		void Sort()
		{
			for (int x = 0; x < m_scoreboard.size(); x++)
			{
				for (int y = 0; y < m_scoreboard.size() - 1; y++)
				{
					if (m_scoreboard[y].score < m_scoreboard[y+1].score)
					{
						Entry temporary = m_scoreboard[y+1];
						m_scoreboard[y+1] = m_scoreboard[y];
						m_scoreboard[y] = temporary;
					}
				}
			}
		}

private:
	std::vector<Entry> m_scoreboard;
};
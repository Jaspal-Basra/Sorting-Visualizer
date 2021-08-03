#include "Bar.h"

void Bar::initializeVariables()
{
	//std::cout << "Enter number of bars: ";
	//std::cin >> numberOfBars;
	this->numberOfBars = NUMBER_OF_BARS;
	this->barSize = WINDOW_WIDTH / static_cast<float>(numberOfBars); // Size of each bar = window width/# of total bars
	this->barCount = 0;
}

/**
* Initializes bars
*/
void Bar::initBars()
{
	float xPos, yPos;

	// Initialize Bars
	this->bar.setPosition(0.f, WINDOW_HEIGHT);
	this->bar.setSize(sf::Vector2f(2.f, 300.f));
	this->bar.setFillColor(sf::Color::Cyan);
	this->bar.setOutlineColor(sf::Color::Black);
	this->bar.setOutlineThickness(1.f);

	// Generate all bars
	while (this->bars.size() < this->numberOfBars)
	{
		// Generate a random height for the bar
		float barHeight = static_cast<float>(rand() % static_cast<int>((WINDOW_HEIGHT)));

		this->bar.setSize(sf::Vector2f(this->barSize, barHeight));

		xPos = barSize * static_cast<float>(barCount);
		yPos = WINDOW_HEIGHT - bar.getSize().y;

		this->bar.setPosition(xPos, yPos);

		// Spawn the bar
		this->bars.push_back(this->bar);
		this->barCount += 1;
	}
}

Bar::Bar()
{
	this->initializeVariables();
	this->initBars();
}

Bar::~Bar()
{
}

void Bar::update()
{
	this->updateBars();
}

void Bar::updateBars()
{
	// float xPos, yPos;

	//quickSort(bars, 0, bars.size() - 1);
	// bubbleSort(bars, bars.size());

	// Update positions of all bars after sort
	// for (int i = 0; i < bars.size(); i++)
	// {
	// 	xPos = barSize * static_cast<float>(i);
	// 	yPos = WINDOW_HEIGHT - bars[i].getSize().y;
	// 	this->bars[i].setPosition(xPos, yPos);
	// }
}

/**
* Renders game objects for display on winow
*/
void Bar::render(sf::RenderTarget& target)
{
	this->renderBars(target);
}

/*
* Renders bars for display on window
*/
void Bar::renderBars(sf::RenderTarget& target)
{
	// Rendering all the bars
	for (int i = 0; i < bars.size(); i++)
	{
		target.draw(bars[i]);
	}
}

int Bar::partition(std::vector<sf::RectangleShape>& A, int start, int end)
{
	int pivot = A[end].getSize().y;
	int partitionIndex = start;

	for (int i = start; i < end; i++)
	{
		if (A[i].getSize().y <= pivot)
		{
			swap(A, i, partitionIndex);
			partitionIndex++;
		}
	}
	swap(A, end, partitionIndex);

	return partitionIndex;
}

void Bar::merge(std::vector<sf::RectangleShape>& A, std::vector<sf::RectangleShape>& left, std::vector<sf::RectangleShape>& right, int n, int nLeft, int nRight)
{
	int i = 0;
	int j = 0;
	int k = 0;
	while (j < nLeft && k < nRight)
	{
		if (left[j].getSize().y <= right[k].getSize().y)
		{
			A[i] = left[j];
			j++;
		}
		else if (right[k].getSize().y < left[j].getSize().y)
		{
			A[i] = right[k];
			k++;
		}
		i++;
	}
	while (j < nLeft)
	{
		A[i] = left[j];
		j++;
		i++;
	}
	while (k < nRight)
	{
		A[i] = right[k];
		k++;
		i++;
	}
}

void Bar::swap(std::vector<sf::RectangleShape>& A, int a, int b)
{
	sf::RectangleShape temp = A[a];
	sf::Vector2f aPos = A[a].getPosition();
	sf::Vector2f bPos = A[b].getPosition();

	/*
	while (A[a].getPosition().x != bPos.x && A[b].getPosition().x != aPos.x)
	{
		if (aPos.x <= bPos.x)
		{
			A[a].move(1.f, 0.f);
			A[b].move(-1.f, 0.f);
		}
		else
		{
			A[a].move(-1.f, 0.f);
			A[b].move(1.f, 0.f);
		}
	}
	*/

	A[a] = A[b];
	A[b] = temp;
}

void Bar::quickSort(std::vector<sf::RectangleShape>& A, int start, int end)
{
	int partitionIndex;

	if (start < end)
	{
		partitionIndex = partition(A, start, end);
		quickSort(A, start, partitionIndex - 1);
		quickSort(A, partitionIndex + 1, end);
	}
}

void Bar::mergeSort(std::vector<sf::RectangleShape>& A, int n)
{
	if (n < 2) return; // Base case (recursion)

	int mid = n / 2;

	std::vector<sf::RectangleShape> left;
	std::vector<sf::RectangleShape> right;

	for (int i = 0; i < mid; i++)
		left.push_back(A[i]);

	for (int i = mid; i < n; i++)
		right.push_back(A[i]);

	mergeSort(left, mid);
	mergeSort(right, n - mid);
	merge(A, left, right, n, mid, n - mid);
}

void Bar::insertionSort(std::vector<sf::RectangleShape>& A, int n)
{
	float val;
	int hole;

	for (int i = 1; i < n; i++)
	{
		val = A[i].getSize().y;
		hole = i;

		while (hole > 0 && A[hole - 1].getSize().y > val)
		{
			A[hole] = A[hole - 1];
			hole--;
		}
		A[hole].setSize(sf::Vector2f(A[hole].getSize().x, val));
	}
}

void Bar::bubbleSort(std::vector<sf::RectangleShape>& A, int n)
{
	int hasSwapOccurred = false;
	for (int k = 1; k < n - 1; k++)
	{
		hasSwapOccurred = false;
		for (int i = 0; i < n - k; i++)
		{
			if (A[i].getSize().y > A[i + 1].getSize().y)
			{
				hasSwapOccurred = true;
				swap(A, i, i + 1);
			}
		}

		if (!hasSwapOccurred)
			return;
	}
}

void Bar::selectionSort(std::vector<sf::RectangleShape>& A, int n)
{
	int i_min = 0;

	for (int k = 0; k < n - 1; k++)
	{
		i_min = k;
		for (int i = k + 1; i < n; i++)
		{
			if (A[i].getSize().y < A[i_min].getSize().y)
				i_min = i;
		}
		if (A[i_min].getSize().y < A[k].getSize().y)
			swap(A, k, i_min);
	}
}

/*
char c;
std::cout << "Select a sorting algorithm from the following:\nSelection Sort (S)\nBubble Sort (B)\nInsertion Sort (I)\nMerge Sort (M)\nQuick Sort (Q)\nEnter here: ";
std::cin >> c;

switch (c)
{
case 'S': sorting.selectionSort(bars, bars.size()); break;
case 'B': sorting.bubbleSort(bars, bars.size()); break;
case 'I': sorting.insertionSort(bars, bars.size()); break;
case 'M': sorting.mergeSort(bars, bars.size()); break;
case 'Q': sorting.quickSort(bars, 0, bars.size() - 1); break;
default: std::cout << "Invalid sorting algorithm selected." << std::endl; break;
}
*/

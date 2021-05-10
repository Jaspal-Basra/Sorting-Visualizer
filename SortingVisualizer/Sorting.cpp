#include "Sorting.h"

int Sorting::partition(std::vector<sf::RectangleShape>& A, int start, int end)
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

void Sorting::merge(std::vector<sf::RectangleShape>& A, std::vector<sf::RectangleShape>& left, std::vector<sf::RectangleShape>& right, int n, int nLeft, int nRight)
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

void Sorting::swap(std::vector<sf::RectangleShape>& A, int a, int b)
{
	sf::RectangleShape temp = A[a];
	A[a] = A[b];
	A[b] = temp;
}

Sorting::Sorting()
{
}

Sorting::~Sorting()
{
}

void Sorting::quickSort(std::vector<sf::RectangleShape>& A, int start, int end)
{
	int partitionIndex;

	if (start < end)
	{
		partitionIndex = partition(A, start, end);
		quickSort(A, start, partitionIndex - 1);
		quickSort(A, partitionIndex + 1, end);
	}
}

void Sorting::mergeSort(std::vector<sf::RectangleShape>& A, int n)
{
	if (n < 2) return; // Base case (recursion)

	int mid = n / 2;

	//std::vector<sf::RectangleShape>* left = new std::vector<sf::RectangleShape>;
	//std::vector<sf::RectangleShape>* right = new std::vector<sf::RectangleShape>;

	std::vector<sf::RectangleShape> left;
	std::vector<sf::RectangleShape> right;

	for (int i = 0; i < mid; i++)
		left.push_back(A[i]);

	for (int i = mid; i < n; i++)
		right.push_back(A[i]);

	mergeSort(left, mid);
	mergeSort(right, n - mid);
	merge(A, left, right, n, mid, n-mid);
}

void Sorting::insertionSort(std::vector<sf::RectangleShape>& A, int n)
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

void Sorting::bubbleSort(std::vector<sf::RectangleShape>& A, int n)
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

void Sorting::selectionSort(std::vector<sf::RectangleShape>& A, int n)
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

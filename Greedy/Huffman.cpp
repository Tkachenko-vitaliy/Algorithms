#include "Huffman.h"

#include <queue>

template<>
struct std::less<Node*>
{
	bool operator() (const Node* nodeFirst, const Node* nodeSecond) const
	{
		return nodeFirst->frequency > nodeSecond->frequency;
	}
};



void Huffman::assign(std::istream& stream)
{
	createFrequencyMap(stream);
	createCodeTree();
	createDictionary();

	stream.clear();
	stream.seekg(0, std::ios_base::beg);
	encode(stream);
}

void Huffman::createFrequencyMap(std::istream& stream)
{
	frequencyMap.clear();

	while (!stream.eof())
	{
		char c = stream.get();
		auto findItem = frequencyMap.find(c);
		if (findItem != frequencyMap.end())
		{
			findItem->second++;
		}
		else
		{
			frequencyMap.insert({ c,1 });
		}
	}
}

void Huffman::createCodeTree()
{
	std::priority_queue<Node*> queue;

	for (auto& item : frequencyMap)
	{
		queue.push(new Leaf{ item.second, item.first });
	}

	auto ExtractNode = [&queue]() -> Node*
	{
		Node* n = queue.top();
		queue.pop();
		return n;
	};

	size_t count = queue.size() - 1;

	for (size_t counter = 1; counter <= count; counter++)
	{
		Node* newNode = new Node;
		newNode->left = ExtractNode();
		newNode->right = ExtractNode();
		newNode->left->parent = newNode;
		newNode->right->parent = newNode;
		newNode->frequency = newNode->left->frequency + newNode->right->frequency;
		queue.push(newNode);
	}

	codeTree.reset(queue.top());
}

void Huffman::createDictionary()
{
	dictionary.clear();
	iterateTree(codeTree.get());
}

void Huffman::iterateTree(Node* node)
{
	if (node == nullptr)
	{
		return;
	}

	if (node->isLeaf())
	{
		CodeString str;
		Node* current = node;
		while (current->parent)
		{
			bool value = isChildRight(current);
			str.insert(str.begin(), value);
			current = current->parent;
		}
		dictionary.emplace(node->getChar(), str);
	}
	else
	{
		iterateTree(node->left);
		iterateTree(node->right);
	}
}

bool Huffman::isChildLeft(Node* nodeChild)
{
	return nodeChild->parent->left == nodeChild;
}

bool Huffman::isChildRight(Node* nodeChild)
{
	return nodeChild->parent->right == nodeChild;
}

void Huffman::encode(std::istream& stream)
{
	encodedData.clear();

	while (!stream.eof())
	{
		char c;
		stream >> c;
		auto pr = dictionary.find(c);
		assert(pr != dictionary.end()); //The character must be presented in tree. Was it created? Is the stream the same?
		CodeString& code = pr->second;
		pushBits(code);
	}
}

void Huffman::pushBits(CodeString& code)
{
	encodedData.insert(encodedData.end(), code.begin(), code.end());
}

void Huffman::getEncoded(std::ostream& stream)
{
	resetPosData();
	
	while (!eof())
	{
		stream << getDataBit();
	}
}

void Huffman::getDecoded(std::ostream& stream)
{
	resetPosData();

	while (!eof())
	{
		Node* n = codeTree.get();
		while (n)
		{
			bool bit = getDataBit();
			if (bit)
			{
				n = n->right;
			}
			else
			{
				n = n->left;
			}
			if (n->isLeaf())
			{
				stream << n->getChar();
				break;
			}
		}
	}
}

void  Huffman::resetPosData()
{
	curPosEncodedData = 0;
}

bool  Huffman::getDataBit()
{
	bool bit = encodedData[curPosEncodedData];
	curPosEncodedData++;
	return bit;
	
}

bool  Huffman::eof()
{
	return curPosEncodedData >= encodedData.size();
}
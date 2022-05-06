class Adjacentlist {
private:
    Adjacentlist* next;
    int x, y;

public:
    Adjacentlist()
    {
        this->next = nullptr;
    }
    Adjacentlist(Adjacentlist* next, int x, int y)
    {
        this->next = next;
        this->x = x;
        this->y = y;
    }
    int getX()
    {
        return this->x;
    }
    int getY()
    {
        return this->y;
    }
    Adjacentlist* getNext()
    {
        return this->next;
    }
    bool changeNext(Adjacentlist* next);
};
bool Adjacentlist::changeNext(Adjacentlist* next)
{
    this->next = next;
    return true;
}
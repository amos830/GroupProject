#include "ListItem.h"
#include "record.h"


ListItem::ListItem(record* data)
{
	this->data = data;
}

ListItem::~ListItem()
{
	delete data;
}

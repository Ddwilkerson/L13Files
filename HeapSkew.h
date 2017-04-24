#if !defined HEAPSKEW_H
#define HEAPSKEW_H

#include "BinaryTree.h"
#include "wx/wx.h"

template < class T >
class HeapSkew : public Drawable
{

   private:
      BinaryTree<T>* bt;
      int sze;
      BinaryTree<T>* merge(BinaryTree<T>* left, BinaryTree<T>* right);

      int (*compare_items) (T* item_1, T* item_2);

   public:
      HeapSkew(int (*comp_items) (T* item_1, T* item_2));
      ~HeapSkew();

      bool heapIsEmpty();
      void heapInsert(T* item);
      T* heapRemove();

      void draw(wxDC& dc, int width, int height);
      void mouseClicked(int x, int y);

};

// this is a MAXHEAP (largest items to top alphabetical order)
template < class T >
HeapSkew<T>::HeapSkew(int (*comp_items) (T* item_1, T* item_2)) : Drawable()
{
   bt = new BinaryTree<T>();
   sze = 0;

   compare_items = comp_items;
}

template < class T >
HeapSkew<T>::~HeapSkew()
{
   delete bt;
}

template < class T >
bool HeapSkew<T>::heapIsEmpty()
{
   return sze == 0;
}

template < class T >
BinaryTree<T>* HeapSkew<T>::merge(BinaryTree<T>* left, BinaryTree<T>* right)
{
  //DO THIS
	BinaryTree<T>* result;

	if(left->isEmpty())
	{
		return right;
	}
	if(right->isEmpty())
	{
		return left;
	}

	int compare = (*compare_items) (left->getRootItem(), right->getRootItem());

	if(compare < 0)
	{
		result = merge(right, left);
	}
	else
	{
		result = left;
	}

	BinaryTree<T>* left_left = result->detachLeftSubtree();
	BinaryTree<T>* left_right = result->detachRightSubtree();

	result->attachRightSubtree(left_left);

	if(left_right->isEmpty())
	{
		result->attachLeftSubtree(right);
		delete left_left;
		delete left_right;
		return result;
	}
	else
	{
		result->attachLeftSubtree( merge(left_right,right) );
		delete left_left;
		delete left_right;
		return result;
	}
}

template < class T >
void HeapSkew<T>::heapInsert(T* item)
{
   //DO THIS (calls merge, should be short)
	 BinaryTree<T>* right = new BinaryTree<T>(item);
	 bt = merge(bt, right);
}

template < class T >
T* HeapSkew<T>::heapRemove()
{
   //DO THIS (calls merge, should be short)
	 T* item = bt->getRootItem();

	 BinaryTree<T>* left = bt->detachLeftSubtree();
	 BinaryTree<T>* right = bt->detachRightSubtree();
	 bt = merge(right,left);
	 delete left;
	 delete right;

	 return item;
}

template < class T >
void HeapSkew<T>::draw(wxDC& dc, int width, int height)
{
   bt->draw(dc, width, height);
}

template < class T >
void HeapSkew<T>::mouseClicked(int x, int y) {bt->mouseClicked(x, y);}

#endif

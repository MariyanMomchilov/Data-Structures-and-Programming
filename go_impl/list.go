package dllist

import (
	"bytes"
	"strconv"
)

type node struct {
	data int
	prev *node
	next *node
}

// LinkedList - Double Linked List of type int
type LinkedList struct {
	first *node
	last  *node
	size  int
}

// PushBack - append element to list
func (list *LinkedList) PushBack(data int) {
	if list.last == nil {
		list.last = &node{data: data}
		list.first = list.last
	} else {
		list.last.next = &node{data, list.last, nil}
		list.last = list.last.next
	}
	list.size++
}

// PushFront - inserts element in front
func (list *LinkedList) PushFront(data int) {
	if list.first == nil {
		list.first = &node{data: data}
		list.last = list.first
	} else {
		list.first.prev = &node{data, nil, list.first}
		list.first = list.first.prev
	}
	list.size++
}

// InsertAt - inserts element at a given index. If index > size === PushBack
func (list *LinkedList) InsertAt(data, i int) {
	crr := list.first
	for crr != nil && i > 0 {
		crr = crr.next
		i--
	}
	if crr != nil {
		crr.prev.next = &node{data, crr.prev, crr}
		crr.prev = crr.prev.next
		list.size++
	} else {
		list.PushBack(data)
	}
}

// PopBack - removes the last element of the list
func (list *LinkedList) PopBack() bool {
	if list.last == nil {
		return false
	}
	list.last = list.last.prev
	list.last.next = nil
	list.size--
	return true
}

// PopFront - removes the first element of the list
func (list *LinkedList) PopFront() bool {
	if list.first == nil {
		return false
	}
	list.first = list.first.next
	list.first.prev = nil
	list.size--
	return true
}

// PopAt - pops element at a given index
func (list *LinkedList) PopAt(i int) bool {
	crr := list.first
	if i >= list.size || crr == nil {
		return false
	}
	for crr != nil && i > 0 {
		crr = crr.next
		i--
	}
	if crr != nil {
		if crr.prev == nil {
			list.first = crr.next
			list.first.prev = nil
		} else {
			crr.prev.next = crr.next
		}

		if crr.next == nil {
			list.last = crr.prev
			list.last.next = nil
		} else {
			crr.next.prev = crr.prev
		}
		return true
	}
	return false
}

// Empty - bool
func (list *LinkedList) Empty() bool {
	return list.size == 0
}

// Size - return the size of the list
func (list *LinkedList) Size() int {
	return list.size
}

func (list LinkedList) String() string {
	var byteBuffer bytes.Buffer
	crr := list.first

	for crr != nil {
		byteBuffer.WriteString(strconv.Itoa(crr.data))
		byteBuffer.WriteString(" <-> ")
		crr = crr.next
	}
	byteBuffer.WriteString(" nil ")
	return byteBuffer.String()
}

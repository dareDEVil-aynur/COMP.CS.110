#include "cards.hh"

Cards::Cards(): top_(nullptr){

}

Card_data* Cards::get_topmost(){
    return top_;
}

void Cards::add(int id){
    Card_data* new_item = new Card_data{id, nullptr};
    new_item->data = id;
    new_item->next = top_;
    top_ = new_item;
}

void Cards::print_from_top_to_bottom(std::ostream& s){
    int i = 1;
    Card_data* current = top_;
    while (current != nullptr){
        s << i << ": " << current->data << std::endl;
        current = current->next;
        i++;
    }
}

bool Cards::remove(int& id){
    if ( top_ == nullptr ) {
       return false;
    } else {
        Card_data* item_to_be_removed = top_;
        id = item_to_be_removed->data;
        top_ = top_->next;
        delete item_to_be_removed;
        return true;
    }
}

bool Cards::bottom_to_top(){
    if (top_ == nullptr || top_->next == nullptr){
        return false;
    } else {
        Card_data* current = top_;
        while (current->next->next != nullptr) {
          current = current->next;
        }
        Card_data* last_card = current->next;
        current->next = nullptr;
        last_card->next = top_;
        top_ = last_card;
        return true;
      }
}

bool Cards::top_to_bottom(){
    if (top_ == nullptr || top_->next == nullptr) {
      return false;
    } else {
      Card_data* current = top_;
      while (current->next != nullptr) {
        current = current->next;
      }
      current->next = top_;
      top_ = top_->next;
      current->next->next = nullptr;
      return true;
    }
}

void Cards::print_from_bottom_to_top(std::ostream& s){
    recursive_print(top_, s);
}

int Cards::recursive_print(Card_data* top, std::ostream& s) {
  if (top == nullptr) {
    return 0;
  } else {
    int index = recursive_print(top->next, s);
    s << (index + 1) << ": " << top->data << std::endl;
    return index + 1;
  }
}

Cards::~Cards(){
    Card_data* current = top_;
    while (current != nullptr){
        Card_data* next = current->next;
        delete current;
        current = next;
    }
}

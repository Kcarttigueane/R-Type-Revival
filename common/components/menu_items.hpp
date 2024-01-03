#if !defined(MENU_ITEM_HPP)
#    define MENU_ITEM_HPP

#    include <functional>
#    include <string>

struct MenuItemComponent {
    std::string label;
    int index;
    bool isSelected;
};

#endif  // MENU_ITEM_HPP
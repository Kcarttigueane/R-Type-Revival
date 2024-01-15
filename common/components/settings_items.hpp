#if !defined(SETTINGS_ITEMS_HPP)
#    define SETTINGS_ITEMS_HPP

#    include <string>
#    include <vector>

struct SettingItemComponent {
    std::string name;
    std::vector<std::string> values;
    int currentValueIndex;
    bool isSelected;
};

#endif  // SETTINGS_ITEMS_HPP
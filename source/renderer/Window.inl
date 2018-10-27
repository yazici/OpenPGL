/**
 * Функция предназначенная для вывода сообщеия.
 *
 * @param title титульник сообщения
 * @param text текст передающий основную суть сообщения
 * @param mesType тип сообщения
 * @param args названия кнопок типа 'const string_view'
 * @return номер нажатой кнопки
 */
template<typename... Types>
static int32_t messege(const string_view& title, const string_view& text, MessegeBoxType mesType, const Types&... args)
{
    using std::vector;
    using std::cerr;
    using std::endl;
    
    int32_t buttonValue = 0;
    vector<SDL_MessageBoxButtonData> buttons(sizeof ...(Types));
    auto p = vector<const string_view>{args...};
    
    for (size_t i = 0; i < buttons.size(); i++, buttonValue++) {
        buttons[i].flags = (buttons.size() - i == 1);
        buttons[i].buttonid = buttonValue;
        buttons[i].text = p[i].data();
    }
    
    SDL_MessageBoxData messageBoxData = {
        mesType,
        nullptr,
        title.data(),
        text.data(),
        (Sint32)buttons.size(),
        &buttons[0],
        nullptr
    };
    
    if (SDL_ShowMessageBox(&messageBoxData, &buttonValue) < 0) {
        cerr << "Error: " << InitSystem::getSysError() << endl;
    }
    
    return buttonValue;
}

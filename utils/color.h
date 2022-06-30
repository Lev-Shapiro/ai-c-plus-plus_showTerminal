void color(string color, string text, bool newLine)
{
    string col = "\033[0m";

    if (color == "blue")
        col = "\033[0;34m";
    else if (color == "green")
        col = "\033[0;32m";
    else if (color == "cyan")
        col = "\033[0;36m";
    else if (color == "red")
        col = "\033[0;31m";
    else if (color == "magenta")
        col = "\033[0;35m";
    else if (color == "yellow")
        col = "\033[0;33m";

    cout << col << text << "\033[0m";
    if (newLine)
    {
        cout << endl;
    }
}
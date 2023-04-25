# C++ Todo List Console Application
This is a console-based todo list application written in C++. The application allows the user to create, modify, and delete todo items, and mark them as done or not done. The todo list is displayed in the console, and the user can navigate through the items using the keyboard.

![preview](https://user-images.githubusercontent.com/81848639/233834035-dcd5a50b-b48b-4c97-88e4-e0e0cd77a16b.png)

## Requirements
To compile and run this application, you need:
- A C++ compiler (e.g., g++)
- The `ncurses` library (for console input/output)
- `make` already installled

## How to run
To run this project, type `make run` in the terminal

## How to use
Once you start the application, you will see a list of todo items in the console, along with some instructions on how to navigate and modify the list. The available commands are:

**In NORMAL MODE:**
- `ENTER` or `x` or `SPACE`: toggle the selected item as done or not done.
- `n`: create a new todo item.
- `d`: delete the selected todo item.
- `UP ARROW`: move the selection up.
- `DOWN ARROW`: move the selection down.
- `e`: edit the selected todo item. (This will enter `EDIT MODE`)

**In EDIT MODE**
- `BACKSPACE`: delete the last character of the editing item.
- `CTRL + BACKSPACE`: delete a word
- **any other key**: append the key to the editing item.
- `ENTER`: save the editing item (back to NORMAL MODE).

To exit the application, press `q` or `CTRL+C`.

## Contributing
If you find a bug or have a suggestion for improvement, feel free to open an issue or submit a pull request. This project is open to contributions, and any help is appreciated!

## License
This project is released under the [MIT License](/LICENSE). Feel free to use it for any purpose.

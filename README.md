# PriorityPusher (Work In Progress)
A simple standalone CLI application made in C for better priority management.

## Usage
```sh
# Add new activity
prioritypusher new

# Display a list of your ToDos
prioritypusher list [-d]
# More in docs!
```

## Documentation
 - `new` Command
 
 Simply put you into an interactive form-like shell
 - `list` Command
 
 This action will list all of your ToDos. You can change the output on your will
 - `top` Command
 
 This action will only show you the top ToDo from sorted list of your ToDos
 - `remove` Command

 This action will remove task from the list
 - `finish` Command

 This action will mark task as finished

 Short Flag | Long Flag | Description
 ---------- | --------- | -----------
 -a         | --asc     | Sort ToDos in ascending order (Default)
 -d         | --desc    | Sort ToDos in descending order

Dibuat di Indonesia

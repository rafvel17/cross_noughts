# Cross noughts

Tic-Tac-toe like game written with winapi.

An extended version of classical 3x3 tic-tac-toe game. 2 players compete with each other on a **20x20** field. The winning condition is **5** in a row.

# How to build

Use **MS Visual Studio** to build the project, project files are provided.

Or generate **cross_noughts.sln** for **MSBuild** via **CMake**:

	git clone https://github.com/rafvel17/cross_noughts
	cd cross_noughts
	mkdir Build64
	cd Build64
	cmake ../
	C:\Path_to_MSBuild_exe\MSBuild.exe cross_noughts.sln

# How to use

Run output **Project_cross_noughts.exe** (basically from PROJ_DIR/x64/Release or /x64/Debug). Press **Файл->Новая Игра** and enjoy!

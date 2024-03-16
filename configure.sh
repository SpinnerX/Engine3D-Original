#!/bin/bash

# Configuration script to configure dependencies for Engine3D

os="$1"

if [[ "$os" = "--linux" ]]; then
	echo "Checking dependencies for Linux..."
	if [ ! -z "/usr/local/include/imgui" ]; then
		echo "Installing Imgui..."
		git clone https://github.com/SpinnerX/Im-Gui ~/Desktop/
		cd ~/Desktop/Im-Gui/ && mkdir build && cd build cmake .. && sudo make -j install
	fi
	
	if [ ! -z "/usr/local/include/glad" ]; then
		echo "Installing glad..."
		git clone https://github.com/SpinnerX/glad
		cd ~/Desktop/glad/ && mkdir build && cd build cmake .. && sudo make -j install
	fi
	
	if [ ! -z "/usr/local/include/ImGuizmo" ]; then
		echo "Downloading Im-Guizmo..."
		git clone https://github.com/SpinnerX/Im-Guizmo ~/Desktop/
		cd ~/Desktop/Im-Guizmo/ && mkdir build && cd build cmake .. && sudo make -j install
	fi
	exit 1
fi

if [[ "$os" = "--mac" ]]; then
	echo "Checking dependencies for Mac..."
	if [ ! -z "/usr/local/include/imgui" ]; then
		echo "Installing Imgui..."
		git clone https://github.com/SpinnerX/Im-Gui ~/Desktop/
		cd ~/Desktop/Im-Gui/ && mkdir build && cd build cmake .. && sudo make -j install
	fi
	
	if [ ! -z "/usr/local/include/glad" ]; then
		echo "Installing glad..."
		git clone https://github.com/SpinnerX/glad
		cd ~/Desktop/glad/ && mkdir build && cd build cmake .. && sudo make -j install
	fi
	
	if [ ! -z "/usr/local/include/ImGuizmo" ]; then
		echo "Downloading Im-Guizmo..."
		git clone https://github.com/SpinnerX/Im-Guizmo ~/Desktop/
		cd ~/Desktop/Im-Guizmo/ && mkdir build && cd build cmake .. && sudo make -j install
	fi

	exit 1
else
	echo "OS \"$os\" is not supported currently!"
fi

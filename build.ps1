
#setup
# Project Dir
#    └---> Obj
#    └---> Src
#    		└--> Include


# -------- BUILD SETTINGS --------
$C_FLAGS = "-Wall", "-Wextra", "-pedantic", "-std=c++20"

$out_file = "nBodies.exe"
$main_files = "Src/main.cpp"

# $src_files =  ""
# $src_files =  "body"
# $src_files =  "utils"
$src_files =  "body", "utils"

$buildAll = $true
$debugBuild = $false


$include_dir = "Src/Include/"

$sdl_inc_dir = "Libs/SDL2/include/SDL2"
$sdl_lib_dir = "Libs/SDL2/lib"
$glm_inc_dir = "Libs/glm"

$sdl_linkables = "-lmingw32", "-lSDL2main", "-lSDL2"


# -------- BUILD SCRIPT --------

# Specifying a Debug or Release Build 
if ($debugBuild) {
	Write-Output "Debug Build"
	$C_FLAGS += "-g3", "-ggdb"	
} else {
	$C_FLAGS += "-O3", "-s", "-ffast-math"
}

if (!(Test-Path("./Obj"))) {
	mkdir Obj
}


# removing previous build
if (Test-Path ./$out_file) {
	Remove-Item $out_file
}


# Compiling
Write-Output "Building:"
foreach ($file in $src_files) {

	if ($file) {
		if ("Src/${file}.cpp" -notin $main_files) {

			if ($buildAll -eq $true) {
				Write-Output "    ${file}.cpp"

				if (Test-Path "Obj/${file}.o") {
					Remove-Item Obj/${file}.o
				}

				g++ $C_FLAGS  -I $include_dir -I $sdl_inc_dir -I $glm_inc_dir -L $sdl_lib_dir $sdl_linkables -o Obj/${file}.o -c Src/${file}.cpp
			}

		}
	}
}



# Linking
$obj_files = Get-ChildItem -Path Obj/

Write-Output "Linking"
g++ $main_files $obj_files $C_FLAGS -o $out_file -I $include_dir -I $sdl_inc_dir -I $glm_inc_dir -L $sdl_lib_dir $sdl_linkables


# Running current build

if (Test-Path ./$out_file) {
	Write-Output "Build Successfully"
	Write-Output ""
	
	./nBodies
}

else {
	Write-Output "ERROR in Building!"
}

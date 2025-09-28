if [ $# -eq 0 ]; then
	echo "Usage: $0 <path-to-extracted-SW-kit>"
	exit 1
fi

TIVAWARE_PATH_INPUT="$1"

if ! grep -q "^export TIVAWARE_PATH=" ~/.bashrc; then
	echo "Setting TIVAWARE_PATH in ~/.bashrc..."
	echo "export TIVAWARE_PATH=$TIVAWARE_PATH_INPUT" >> ~/.bashrc
	echo "Reloading ~/.bashrc to apply changes..."
	source ~/.bashrc
	echo "TIVAWARE_PATH is set to: $TIVAWARE_PATH_INPUT"
else
	echo "TIVAWARE_PATH is already set in ~/.bashrc."
fi
# capture the first argument as project name and navigate to the project directory
PROJECT_NAME="$1"
cd "$PROJECT_NAME"

# check if docker daemon is running, if not start it
if ! docker info > /dev/null 2>&1; then
    echo "Docker is not running. Starting Docker Desktop..."
    open -a Docker
    echo "Waiting for Docker to start..."
    while ! docker info > /dev/null 2>&1; do
        sleep 1
    done
    echo "Docker started successfully."
fi

# if docker images doesn't exist, build the image
if [ -z "$(docker images | grep "tiva-$PROJECT_NAME")" ]; then
    echo "Docker image for project '$PROJECT_NAME' not found. Building the image..."
    docker build -t "tiva-$PROJECT_NAME" .
fi

# run the image
docker run --rm -v "$(pwd)/../../../:/repo" -w /repo/VSCode/MacOS/$PROJECT_NAME tiva-$PROJECT_NAME make clean all

# flash the binary, if build was successful
if [ $? -eq 0 ]; then
    openocd -f board/ti_ek-tm4c123gxl.cfg -c "program build/$PROJECT_NAME.elf verify reset exit"
fi
### Course reference

[YT course](https://www.youtube.com/watch?v=kTp5xUtcalw)

containers / dockers / kubernetes

### Microservices concepts
based on the assumption of breaking down monolithic application with
loosely coupled services connected with fine grained and lightweight communication (usually grpc apis for performance).

functionality and responsibiilities are separated (almost).

different pieces can be independently managed with small teams, different languages can be used as well as different databases
for persisting data. 

they can be scaled and deployed independently

migration strategy, strangler facade pattern -> martin fawler blog
    you put a facade piece on top of the actual services and you start migrating piece by piece


anipatterns:
    unnecessary complexity
    overengineering
    security issues with communication
    processes overhead
    new figures specialised figures required (devops)
    it is not magic, and it comes with complexities
    
pro:
    improved fault isolation
    eliminate vendor or technology lock in
    easier and faster to deploy and scale

cons:
    development and process complexity
    system and integration testing harder to achieve
    potential multiple database to manage
    latency issues (partially solved with grpc)
    transient errors (mostly due to network fallibility)
    new processeses added for automating deployments
    multiple point of failures
    security


### Cloud native
containers & orchestration:
    application and services packed in container and orchestrated via kube
    
immutable and disposable infrastructure:
    we don't patch or update, you dispose and replace with a new version
    
declarative:
    define a desired state (like run at 85% capacity, or run 3 copies of the service)

service meshes:
    communication are managed via service meshes used to handle security, routing and observability

services are loosely coupled

ci/cd pipelines and testing is automated

movement primarily lead by open source technologies

is all about speed and agility in deployment
    clean code -> ddd -> microservices -> kube

easier with new project

check the trail map

### Containers introduction
faster to deploy
run everywhere
isolated
faster automation

vm virtualise hardware with os, container virtualise an operating system (they do not boot)

vm large footprint, slow to boot, ideal for running tasks
c quick lightweight portable for short lived tasks, pack more contaienr on same server (more density)

contianer, layering:
    base os + customisation (pkgs) + application
    
docker pull for getting an image

conatiner registry
    centralisd repo for containers
    
orchestrator
    manage infrastructure. contaienr, deployment, scaling, faiover, helth monitoring, app upgrade and zero downtime
    
    
### Docker
offer:
    contaier runtime
    command line tool
    dockerfile for building containers

docker desktop easier starting point:
    can be conected with remote registry (~ to git and github with repositories) with docker hub

cli:
    docker info     -> system info, all container and system information
    docker version  -> system version, for docker engine
    docker login    -> log in docker registry (default to docker hub)
    docker ps (-a)  -> list running (and stopped) containers
    docker pull <image-name>        -> pull image from registry
    docker run (-d) <image-name>    -> run containers (detached)
    docker start <container-name>   -> start stopped containers
    docker stop <container-name>    -> stop running containers
    docker kill <container-name>    -> kill containers, usually not used
    docker image inspect <image-name>       -> get image info
    docker run --memory="256m" <image-name> -> run container with max memory limit
    docker run --cpus=".5" <image-name>     -> run container with max cpu limit
    docker rm <container-name>      -> remove stopped container from memory
    docker rm $(docker ps -a -q)    -> remove all stopped conatiners from memory
    docker images                   -> list local image
    docker rmi <image-name>         -> remove the image
    docker run -it <image-name> -- /bin/bash            -> run a container and attach a shell directly
    docker container exec -it <container-name> -- bash  -> attach shell to a running container
    docker build -t [name:tag] .                -> build with dockerfile in current directory
    docker build -t [name:tag] -f <filename>    -> build with specific filename for the docker file, usually in different location
    docker tag <image-name> [name:tag]          -> tag an existing image, specify version number
    
    
Docker Image: 
    A read-only blueprint or snapshot. 
    It contains everything an application needs to run: the code, libraries, dependencies, and environment settings. 
    It is "frozen" and cannot be changed once built.

Docker Container: 
    A live, running instance of an image. 
    When you "run" an image, it becomes a container. 
    Unlike an image, a container is a process that exists in memory and has a writable layer where it can store temporary data. 


Dockerfile contains building steps for creating and run the containers

Tagging:
    create a target image
    can be done with:
        [name:tag] combination
        [repository/name:tag] -> in case of remote or different repository

You can add shell aliases inside the container by adding the following to a Dockerfile:
#### For Bash users
RUN echo "alias l='ls -alf'" >> /root/.bashrc
#### For Alpine/Sh users
RUN echo "alias l='ls -alf'" >> /etc/profile


### Persist data
Container per se are stateless and ephimeral entities and therefor they do not persist data when stopped.

If data persistency is required we store it outside the container in what is called a volume.

A volume is an object used a folder on the host machine to a logical folder inside the container.

Volumes are stored in a part of the host filesystem that is managed by Docker (usually /var/lib/docker/volumes/ on Linux). This is the best way to persist data in Docker.

Bind Mounts is another way to persist data: These link a specific, user-defined path on the host machine (like /Users/you/project/config) to a folder in the container. These are great for source code during development.

cli:
    docker volume create <volume-name>  -> creating a volume
    docker volume ls                    -> list all the volumes
    docker volume inspect <volume-name> -> volume info
    docker volume rm <volume-name>      -> remove a volume
                                           can be removed only after all the attached container are removed
    
Run a container with a volume:
    docker run -d --name <container-name> -v data:/var/lib/data <image-name>:<tag> --> volumes
    docker run -d --name <container-name> -v /host/path:/container/path <image-name>:<tag> --> bind mounts

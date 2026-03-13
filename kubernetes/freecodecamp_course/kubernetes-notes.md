### Kubernetes concepts

Overview
    The leading container orchestration tool.
    Vendor neutral and open source.
    Runs on all major cloud providers.
    Provides a unified API.

Capabilities
    Service discovery and load balancing.
    Storage orchestration.
    Automated rollouts and rollbacks.
    Self-healing (restarting/replacing failed containers).
    Secret and configuration management.

Limitations
    Does not deploy or build applications or containers.
    Does not provide application-level services (e.g., native cache, databases, or message buses).

---

### Architecture

1. The Control Plane (Master)
    The Control Plane makes global decisions about the cluster and detects/responds to events.

    - kube-apiserver: It is the central hub that all components and users (via kubectl) talk to.

    - etcd: A consistent and highly-available key-value store that holds all cluster data. It serves as source of truth.

    - kube-scheduler: It watches for new Pods and assigns them to a specific Node based on resource availability.

    - kube-controller-manager: It runs control loops to ensure the current state of the cluster matches the desired state (e.g., if a node goes down, it notices and starts new pods).

    - cloud-controller-manager: It links your cluster into your cloud provider's API (AWS, GCP, Azure) to manage things like load balancers and storage.


2. Worker Nodes

    These are the machines (VMs or physical servers) that actually run your applications.

    - Kubelet: An agent that runs on each node to ensure that the containers described in Pod specifications are running and healthy. It manage pods lifecycle.

    - Kube-proxy: It maintains network rules on nodes, allowing network communication to your Pods from inside or outside the cluster.

    - Container Runtime: The software responsible for actually running the containers (e.g., containerd, CRI-O).

    - Pod: The smallest unit in Kubernetes; a wrapper that hosts one or more containers.


How they work together

    User sends a command (e.g., kubectl apply) to the API Server.
    The API Server updates etcd.
    The Scheduler notices the new requirement and picks a Worker Node.
    The Kubelet on that node receives the instruction and tells the Container Runtime to start the container.
    Kube-proxy sets up the networking so users can reach the app.


Hierarchical structure
cluster -> nodes -> pods -> containers

---

### Context

A context is a group of access parameters that defines which cluster, user, and namespace kubectl commands should target.

FILE LOCATION:
The configuration is typically stored in: $HOME/.kube/config (YAML format).

COMPONENTS:
- Cluster: The specific Kubernetes cluster.
- User: The credentials used to authenticate.
- Namespace: The default namespace for the context.

CLI COMMANDS:
- View current context:
  kubectl config current-context

- List all contexts:
  kubectl config get-contexts

- Switch context:
  kubectl config use-context <context-name>

- Delete a context:
  kubectl config delete-context <context-name>

- Rename a context:
  kubectl config rename-context <old-name> <new-name>

---

### Namespaces

DEFINITION
Namespaces are logical partitions within a single physical cluster used to group and isolate resources. They are commonly used to separate environments such as dev, test, and prod.

CORE CONCEPTS
- Logical Isolation: Used to group resources logically (dev, test, prod).
- Cascading Deletion: Deleting a namespace automatically deletes all objects within it.
- Connectivity: Objects in one namespace can typically access objects in other namespaces unless restricted.
- Policies: Network policies and resource quotas are defined at the namespace level.

YAML EXAMPLES

```yaml
1. Namespace Definition:
apiVersion: v1
kind: Namespace
metadata:
    name: prod

2. Pod Assignment:
apiVersion: v1
kind: Pod
metadata:
    name: application-name
    namespace: prod # Reference the namespace here
spec:
    containers:
    - name: nginx-container
      image: nginx
```

CLI COMMANDS (Alias: ns)
- List all namespaces:
  kubectl get ns

- Create a namespace:
  kubectl create ns <namespace-name>

- Delete a namespace:
  kubectl delete ns <namespace-name>

- Switch current context namespace:
  kubectl config set-context --current --namespace=<namespace-name>

- List pods in a specific namespace:
  kubectl get pods -n <namespace-name>

- List pods in all namespaces:
  kubectl get pods --all-namespaces

---

### Create resources

1. DECLARATIVE (Recommended)
- Method: Uses YAML files and 'kubectl apply' or 'create' to define the "Desired State."
- Benefits: Repeatable, version-controllable (GitOps), and portable.
- Sources: Official kubernetes.io documentation or IDE extensions (VS Code).

2. IMPERATIVE
- Method: Direct 'kubectl' commands.
- Best Use: Learning, rapid development, and troubleshooting.

CLI COMMANDS
- Create from file:
  kubectl create -f <yaml-file>

- List deployments:
  kubectl get deploy

- Delete deployment:
  kubectl delete deploy <deploy-name>

---

### Run Kubernetes locally

docker desktop, minikube -> you can only run one node
microk8s, kind => you can run multiple nodes

---

### Nodes: master and worker architecture

### 1. Master nodes (Control plane)
The control plane manages the cluster's state. It is a best practice NOT to run application workloads on master nodes to ensure stability and security.

COMPONENTS:

- kube-apiserver: 
  - The cluster's REST interface and gateway. 
  - The ONLY component that communicates directly with etcd.
  - All clients (kubectl, users, and other components) interact through this API.

- etcd: 
  - A consistent, high-availability key-value store.
  - Acts as the "Single Source of Truth" for all cluster state data.
  - Note: Not to be used as a database for application-specific data.

- kube-controller-manager: 
  - The "Controller of Controllers."
  - Manages various control loops, including:
    - Node Controller: Manages node status.
    - Replication Controller: Maintains the correct number of pods.
    - Endpoints Controller: Populates endpoint objects (joining Services and Pods).
    - Service Account & Token Controllers: Manages API access tokens.

- cloud-controller-manager: 
  - Offloads cloud-specific control logic to interact with provider APIs (AWS, Azure, GCP, etc.).
  - Manages Node (deletion checks), Route (network infra), Service (Load Balancers), and Volume (provisioning) controllers.

- kube-scheduler: 
  - Assigns newly created Pods to specific Worker Nodes.
  - Factors in requirements: Resource needs, hardware/software constraints, Affinity/Anti-affinity, and data locality.

---

### 2. Worker nodes
Physical or virtual machines where the actual application containers run.

DEFAULT SERVICES (Managed by Master):

- Container Runtime: The engine that runs containers (e.g., containerd, CRI-O).
- Kubelet: 
  - The primary "node agent." 
  - Communicates with the API server to ensure containers in Pod specs are running and healthy.
- kube-proxy: 
  - A network proxy that maintains network rules on the node.
  - Enables communication to pods from inside or outside the cluster.

---

### 3. Node pools
Groups of VMs within a cluster that share the same configuration (size, OS, labels).

- Flexibility: A cluster can have multiple pools (e.g., one pool with high-CPU VMs and another with high-RAM).
- Scaling: Each pool can be autoscaled independently based on workload demand.

---

### Pods

DEFINITION
- Represent a unit of deployment that encapsulates one or more application containers.
- Smallest deployable unit in Kubernetes.
- Pods always run on Nodes.

CHARACTERISTICS
- A Pod can run one or multiple tightly coupled containers.
- Containers in the same Pod share:
  - IP address space
  - Mounted volumes
  - Localhost networking (containers communicate via `localhost`)

EPHEMERAL NATURE
- Pods are ephemeral; they are not updated in-place.
- To update, you replace a Pod with a new version (typically with a new IP address).

SCALING
- You scale workloads by deploying more Pods, not by adding more containers into a single Pod.

STATE AND LIFECYCLE
- Pod state and lifecycle are managed by the API server in the control plane.
- The current state is stored and visible in etcd.

POD PHASES
- Pending: Scheduled for creation, but not yet running.
- Running: Pod has been bound to a node and at least one container is running.
- Succeeded: All containers terminated successfully (exit with no error).
- Failed: At least one container terminated with an error.
- Unknown: The state of the Pod cannot be obtained (communication issue with the node).
- CrashLoopBackOff: A container repeatedly fails, Kubernetes restarts it and it fails again.

CLI COMMANDS (Pods)
- Create from file (declarative):
  kubectl create -f <file.yaml>
- Run an ad-hoc Pod:
  kubectl run <pod-name> --image=busybox -it -- /bin/sh
- List Pods:
  kubectl get pods
- List Pods with more details:
  kubectl get pods -o wide
- Describe a Pod (events, state, etc.):
  kubectl describe pod <pod-name>
- Export a Pod definition to YAML:
  kubectl get pod <pod-name> -o yaml > <file.yaml>
- Execute a command inside a Pod:
  kubectl exec -it <pod-name> -- sh
- Delete from file:
  kubectl delete -f <file.yaml>
- Delete a specific Pod:
  kubectl delete pod <pod-name>
- Delete a Pod without waiting for grace period:
  kubectl delete pod <pod-name> --wait=false
- Force delete a Pod (no grace period):
  kubectl delete pod <pod-name> --grace-period=0 --force

---

### INIT CONTAINERS
- Initialize a Pod before the main application containers run.
- Always run to completion.
- You can define more than one; execution is sequential.
- If an init container fails, the kubelet repeatedly restarts it until it succeeds
  (unless `restartPolicy` is set to `Never`).
- Great for validation or setting up infrastructure before application containers run.

---

### LABELS
- Key/value pairs used to identify, describe, and group related sets of objects or resources.
- Attached to objects such as Pods, Nodes, Services, Namespaces, etc.
- Common examples:
  - env=dev, env=prod
  - app=frontend, app=backend
  - nodeType=high-memory, gpu=true

---

### SELECTORS
- Use labels to filter or select objects.
- Used by many Kubernetes resources (Services, Deployments, ReplicaSets, Jobs, etc.).

SCHEDULING WITH NODE LABELS
- Nodes can be labeled (e.g., `nodeType=high-memory`, `zone=eu-west-1a`).
- Pod specs can use those labels (e.g., `nodeSelector`, node affinity) to schedule Pods onto matching Nodes.
- This is useful when different Nodes have different capacities or characteristics (CPU, RAM, GPU, region, etc.).

SERVICES AND POD LABELS
- A Service uses a label selector (`spec.selector`) to determine which Pods it routes traffic to.
- The Service's selector must match the labels on the target Pods; only those Pods become Service endpoints.

---

### MULTI-CONTAINER PODS

OVERVIEW
- Most common scenario: one main container and one or more helper containers.
- Helper containers support the main app (logging, proxying, side tasks, etc.).

SIDECAR PATTERN
- The main app focuses on core logic (e.g., writing log files to a local volume).
- A sidecar container handles supporting work (e.g., shipping logs to persistent/cloud storage, reloading config).

ADAPTER PATTERN
- The main app produces complex or custom-formatted output (e.g., metrics or logs).
- An adapter container transforms that output into a standard format expected by another system (e.g., monitoring/metrics service).

AMBASSADOR PATTERN
- The main app talks to a local "ambassador" container instead of directly to external services.
- The ambassador container proxies and manages connections to external systems (e.g., databases, APIs, message queues).

REFERENCE
- These patterns are described in more detail in "Designing Distributed Systems" by Brendan Burns.

CLI COMMANDS (Multi-container Pods)
- Create a multi-container Pod from a YAML file:
  kubectl create -f <file.yaml>
- Exec into a specific container in a Pod:
  kubectl exec -it <pod-name> -c <container-name> -- /bin/sh
- View logs for a specific container in a Pod:
  kubectl logs <pod-name> -c <container-name>

---

### NETWORK CONCEPTS

- All containers within a Pod share the same network namespace and can communicate with each other over `localhost`.
- By default (without NetworkPolicies), all Pods in the cluster can communicate with each other.
- All Nodes can communicate with all Pods (cluster networking model).
- Pods are given an IP address (ephemeral; changes when Pods are recreated).
- Services are given a stable, virtual IP (`ClusterIP`) for as long as the Service exists.
- Containers inside the same Pod also share volumes (in addition to IP/ports).
- Containers in different Pods can communicate directly via Pod IPs, but Services are typically used to provide stable addressing and load balancing.
- For external access, traffic commonly goes through:
  - A Service of type `LoadBalancer` (cloud provider integration), or
  - An Ingress (HTTP/HTTPS routing at L7).

---

### WORKLOADS

### REPLICA SETS
- Ensure that the desired number of identical Pod replicas are running at any given time.
- Provide basic self-healing: if a Pod dies, the ReplicaSet creates a replacement.
- Maintain the "desired state" for a group of Pods based on label selectors.
- In practice, you usually do not create ReplicaSets directly; you use Deployments.
- Deployments provide more features (rollouts, rollbacks, updates) and manage ReplicaSets for you in the background.

CLI COMMANDS (ReplicaSets)
- Create a ReplicaSet from a definition file:
  kubectl apply -f <definition.yaml>
- List ReplicaSets:
  kubectl get rs
- Describe a specific ReplicaSet:
  kubectl describe rs <rs-name>
- Delete a ReplicaSet using the definition file:
  kubectl delete -f <definition.yaml>
- Delete a ReplicaSet by name:
  kubectl delete rs <rs-name>

---

### DEPLOYMENTS

PODS VS DEPLOYMENTS
- Plain Pods do not self-heal, scale, update, or rollback automatically.
- A Deployment manages a Pod template and ensures the desired state via one or more ReplicaSets.
- Typically, you create one Deployment per microservice you are running.
- Deployments create and manage ReplicaSets for self-healing and scalability and, on top of that, manage updates and rollbacks.

KEY SETTINGS
- `replicas`: Number of Pod instances to run.
- `revisionHistoryLimit`: Number of previous ReplicaSet revisions to keep (for rollbacks).
- `strategy`:
  - `RollingUpdate`: Gradually cycle through Pods, updating them in batches.
  - `Recreate`: Delete all existing Pods before creating new ones.

CLI COMMANDS (Deployments)
- Imperative: create a Deployment:
  kubectl create deploy <deployment-name> --image=busybox --replicas=3 --port=80
- Declarative: create/update a Deployment from a definition file:
  kubectl apply -f <definition.yaml>
- List Deployments:
  kubectl get deploy
- Describe a specific Deployment:
  kubectl describe deploy <deployment-name>
- List ReplicaSets created by Deployments:
  kubectl get rs
- Delete a Deployment using the definition file:
  kubectl delete -f <definition.yaml>
- Delete a Deployment by name:
  kubectl delete deploy <deployment-name>

---
 
### DAEMONSETS

DEFINITION
- Ensure that all Nodes (or a selected subset) run exactly one Pod instance.
- As Nodes are added to the cluster, the DaemonSet automatically schedules a Pod onto those Nodes.
- Commonly used for node-level “daemon” workloads.

HOW IT WORKS (High level)
- The DaemonSet controller ensures the desired Pod is running on matching Nodes.
- The scheduler handles placement in most cases (unless you use special patterns like `hostNetwork`/`nodeName`).

COMMON USE CASES
- Cluster storage daemons.
- Log collection agents on every Node.
- Node monitoring agents on every Node.

CLI COMMANDS (DaemonSets)
- Create/update a DaemonSet from a definition file:
  kubectl apply -f <definition.yaml>
- List DaemonSets:
  kubectl get ds
- Describe a specific DaemonSet:
  kubectl describe ds <ds-name>
- Delete a DaemonSet using the definition file:
  kubectl delete -f <definition.yaml>
- Delete a DaemonSet by name:
  kubectl delete ds <ds-name>

--- 

### STATEFULSETS

DEFINITION
- Designed for workloads that need stable identity and persistent state.
- Each Pod gets a **sticky identity**:
  - Stable Pod name/ordinal (e.g., `app-0`, `app-1`, ...)
  - Stable network identity (via a **headless Service**)
  - Stable storage (PersistentVolumes via PVCs)

BEHAVIOR
- Pods are created **in order** (0 → N) and typically terminated **in reverse order** (N → 0).
- If a Pod dies, it is recreated with the **same identity** (name/ordinal).
- Volumes are **not automatically deleted** when Pods are deleted; the point is to preserve data.

WHEN TO USE
- Stable, unique network identifiers.
- Stateful applications such as databases and distributed systems that require persistent storage.

PRACTICAL NOTE
- If you can, prefer managed/cloud databases for built-in replication, backups, and HA rather than self-managing stateful workloads in-cluster.

CLI COMMANDS (StatefulSets)
- Create/update a StatefulSet from a definition file:
  kubectl apply -f <definition.yaml>
- List StatefulSets:
  kubectl get sts
- Describe a specific StatefulSet:
  kubectl describe sts <sts-name>
- Delete a StatefulSet using the definition file:
  kubectl delete -f <definition.yaml>
- Delete a StatefulSet by name:
  kubectl delete sts <sts-name>

---

### JOBS

DEFINITION
- Workloads for **short-lived, finite tasks**.
- A Job creates one or more Pods and ensures a specified number of them **successfully complete**.

BEHAVIOR
- As Pods complete, the Job tracks successful completions.
- When the required number of successful completions is reached, the Job is considered **complete**.
- By default, Jobs with multiple Pods may run them sequentially; you can configure **parallelism** and **completions** for parallel execution.

COMMON USE CASES
- One-off batch tasks.
- Data processing jobs.
- Maintenance or migration scripts that must eventually complete.

CLI COMMANDS (Jobs)
- Imperative: create a Job:
  kubectl create job <job-name> --image=busybox
- Declarative: create/update a Job from a definition file:
  kubectl apply -f <definition.yaml>
- List Jobs:
  kubectl get job
- Describe a specific Job:
  kubectl describe job <job-name>
- Delete a Job using the definition file:
  kubectl delete -f <definition.yaml>
- Delete a Job by name:
  kubectl delete job <job-name>

---

### CRONJOBS

DEFINITION
- A CronJob creates Jobs on a repeating schedule (like `cron`).
- Think of it as a scheduled Job runner.

SCHEDULING NOTES
- CronJob schedules are interpreted using the controller's time zone (commonly UTC in managed clusters).
- Newer Kubernetes versions support specifying a `timeZone` field; otherwise, plan assuming UTC.

CLI COMMANDS (CronJobs)
- Imperative: create a CronJob (runs every minute):
  kubectl create cronjob <cronjob-name> --image=busybox --schedule="*/1 * * * *" -- /bin/sh -c "date;"
- Declarative: create/update a CronJob from a definition file:
  kubectl apply -f <definition.yaml>
- List CronJobs:
  kubectl get cj
- Describe a specific CronJob:
  kubectl describe cj <cronjob-name>
- Delete a CronJob using the definition file:
  kubectl delete -f <definition.yaml>
- Delete a CronJob by name:
  kubectl delete cj <cronjob-name>


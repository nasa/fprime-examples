# ExamplesDeployment Application

The Examples deployment is designed to showcase the examples in this repository that do not require a specific deployment or deployments of their own (e.g. the hub pattern requires two dedicated deployments and is not instantiated here).

## Building and Running the ExamplesDeployment Application

In order to build the ExamplesDeployment application, or any other F´ application, we first need to generate a build directory. This can be done with the following commands:

```
cd ExamplesDeployment
fprime-util generate
```

The next step is to build the ExamplesDeployment application's code.
```
fprime-util build
```

## Running the application and F' GDS

The following command will spin up the F' GDS as well as run the application binary and the components necessary for the GDS and application to communicate.

```
cd ExamplesDeployment
fprime-gds
```

## Running the application with Ground-Calculated Channels

In order to run the example application with ground-calculated channels, the user must generate the combined dictionary and run the GDS with it.

```
cd ExamplesDeployment
fprime-merge-dictionary --permissive --output MergedDictionary.json \
    ../build-artifacts/Darwin/ExamplesDeployment/dict/ExamplesDeploymentTopologyDictionary.json \
    ../../GdsExamples/gds-plugins/src/ground_channels/GroundDefinedChannelsDictionary.json
fprime-gds --dictionary ./MergedDictionary.json
```

> [!NOTE]
> Ground-calculated channels only works with the `--no-zmq` option.

## Running the example Tests

Start the GDS as shown above, then run:

```
cd ..
pytest
```

# ExternalLibraryIntegration::ImageProcessor

The ImageProcessor is a component that provides a means for components to load onboard images into the component for future processing. When the  `PROCESS_IMAGES` command is invoked, the images that have been loaded into the component are processed.

> [!NOTE]
> This component is a dummy implementation that is meant to demonstrate how to integrate an external library into a component. It does not perform any actual image processing; but shows how an F´ component could encapsulate the OpenCV library.

## Usage Examples


## Commands
| Name | Description |
|---|---|
| `PROCESS_IMAGES` | Process images that are loaded into the internal image array |

## Events
| Name | Description |
| `ImageReadSuccess` | Logs an image read success |
| `ImageReadFailure` | Logs an image read failure |

## Requirements
Add requirements in the chart below
| Name | Description | Validation |
| LIB-IMAGEPROCESSOR-001 | The ImageProcessor component shall load images into its internal array upon request (port call) | Unit Test |
| LIB-IMAGEPROCESSOR-002 | The ImageProcessor component shall process loaded images upon request (ground command) | Unit Test |


# Exporting YOLOv8 and YOLOv5 Models

To export YOLOv8 models:

```commandline
yolo export model=yolov8s.pt imgsz=480,640 format=onnx opset=12
```

To export YOLOv5 models:

```commandline
python3 export.py --weights yolov5s.pt --img 480 640 --include onnx --opset 12
```



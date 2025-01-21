# Ortho-Vision Project

Ortho-Vision is an AI-powered dental application designed to assist dentists in planning optimal therapeutic implant treatments. By leveraging advanced deep learning models for segmentation and object detection, the app analyzes dental radiographs to identify dental structures and anomalies, providing interactive reports and improving the dental implant planning process.

---
## 👥 **Contributors**

- **Rares Dan Tiago Goia** (Babes-Bolyai University, Group 923)
- **Dragos Andrei Gavrus** (Babes-Bolyai University, Group 923)

---
## 📝 **Table of Contents**

- [Introduction](#introduction)
- [Project Overview](#project-overview)
- [Application Functionality](#application-functionality)
- [Experimental Phases](#experimental-phases)
  - [Phase 1: Segmentation](#phase-1-segmentation)
  - [Phase 2: Object Detection - Anomalies Identification](#phase-2-object-detection-anomalies-identification)
  - [Phase 3: Object Detection - Teeth Identification](#phase-3-object-detection-teeth-identification)
  - [Phase 4: Model Improvements and Pipeline](#phase-4-model-improvements-and-pipeline)
- [Technologies Used](#technologies-used)
- [Results](#results)
- [Future Work](#future-work)
- [Contributors](#contributors)

---

## 📖 **Introduction**

Ortho-Vision aims to improve dental implant planning by providing a user-friendly AI-based tool that can segment dental features from radiographs, detect anomalies, and generate interactive reports for dentists. The primary goal is to assist in identifying key dental structures necessary for accurate implant placement.

---

## 💻 **Project Overview**

The project follows a multi-phase approach to develop a robust dental application:

1. **Segmentation Models**: Identifying key dental features in radiographs. This was done foer experimentation purposes, but the model for segmentation is not part of the final application
2. **Object Detection Models**: Detecting anomalies and identifying individual teeth.
3. **Model Improvements**: Enhancing the accuracy and reliability of the AI models.
4. **Integration**: Building a complete web application with a user-friendly interface.

---

## ⚙️ **Application Functionality**

The application includes the following functionalities:

- Upload dental radiographs.
- Detect anomalies in the dental images.
- Identify individual teeth and match them with corresponding anomalies.
- Generate interactive reports for dentists.
- Allow editing of the AI-generated reports to improve accuracy.

---

## 🔬 **Experimental Phases**

### **Phase 1: Segmentation**

#### **Data Collection**
- Public dataset with 1,000 training images and 100 test images.
- Images normalized to a resolution of 256x256.

#### **Methods and Algorithms**
- **Pre-trained Dental Segmentator (Hugging Face)**
- **U-Net Model**: Implemented using TensorFlow and Keras.
  - Experiment 1: Achieved 92% accuracy.
  - Experiment 2: Achieved 94.5% accuracy with optimized batch size and training epochs.

### **Phase 2: Object Detection - Anomalies Identification**

#### **Data Collection**
- Proprietary dataset provided by UMF University.
- 1,000 training images, 100 validation images, and 100 test images.
- 12 classes of dental structures, including implants, caries, and bone conditions.

#### **Methods and Algorithms**
- **YOLOv11 Model**: Pre-trained on the COCO dataset, fine-tuned on the proprietary datasets.

### **Phase 3: Object Detection - Teeth Identification**

#### **Data Collection**
- Proprietary dataset with 1,000 training images and 100 validation/test images.
- 32 classes representing individual teeth.

#### **Methods and Algorithms**
- **YOLOv11 Model**: Used to detect individual teeth and match them with detected anomalies.

### **Phase 4: Model Improvements and Pipeline**

The focus of this phase is to:
- Introduce additional preprocessing steps.
- Experiment with ensemble methods.
- Test advanced architectures to further improve model accuracy.

---

## 🧰 **Technologies Used**

- **Programming Languages**: Python, JavaScript
- **Frontend**: React.js
- **Backend**: Flask
- **Database**: SQL
- **AI Libraries**: TensorFlow, Keras, YOLO, OpenCV, PIL
- **Tools**: Ultralyitcs, Hugging Face

---

## 📊 **Results**

The project achieved significant progress in dental segmentation and detection:

- **U-Net Segmentation Model**: Achieved 94.5% accuracy.
- **YOLOv11 Anomalies Detection Model**: Accurately identified anomalies in dental structures.
- **YOLOv11 Teeth Detection Model**: Achieved a high accuracy rate of 97.5%.

---

## 🚀 **Future Work**

- Expand the dataset to include 3D radiographs.
- Evaluate additional model architectures or improve the existing ones.
- Complete the application as a full-fledged dental implant planning tool.


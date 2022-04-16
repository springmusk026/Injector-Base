#ifndef ESP_H
#define ESP_H

#include <jni.h>
#include "Color.hpp"
#include "Rect.hpp"

class ESP {
private:
    JNIEnv *_env;
    jobject _cvsView;
    jobject _cvs;

public:
    ESP() {
        _env = nullptr;
        _cvsView = nullptr;
        _cvs = nullptr;
    }

    ESP(JNIEnv *env, jobject cvsView, jobject cvs) {
        this->_env = env;
        this->_cvsView = cvsView;
        this->_cvs = cvs;
    }

    bool isValid() const {
        return (_env != nullptr && _cvsView != nullptr && _cvs != nullptr);
    }

    int getWidth() const {
        if (isValid()) {
            jclass canvas = _env->GetObjectClass(_cvs);
            jmethodID width = _env->GetMethodID(canvas, "getWidth", "()I");
            return _env->CallIntMethod(_cvs, width);
        }
        return 0;
    }

    int getHeight() const {
        if (isValid()) {
            jclass canvas = _env->GetObjectClass(_cvs);
            jmethodID width = _env->GetMethodID(canvas, "getHeight", "()I");
            return _env->CallIntMethod(_cvs, width);
        }
        return 0;
    }

    void DrawLine(Color color, float thickness, Vector3 start, Vector3 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawLine",
                                                   "(Landroid/graphics/Canvas;IIIIFFFFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 thickness,
                                 start.X, start.Y, end.X, end.Y);
        }
    }
    
    void DrawText(Color color, float stroke, std::string str, Vector3 pos, float size) {
        
		if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawText",
                                                   "(Landroid/graphics/Canvas;IIIIFLjava/lang/String;FFF)V");
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,stroke,
                                 _env->NewStringUTF(str.c_str()), pos.X, pos.Y, size);
        }
    }
	
	void DrawText360(Color color, float stroke, std::string str, Vector2 pos, float size) {
        
		if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawText",
                                                   "(Landroid/graphics/Canvas;IIIIFLjava/lang/String;FFF)V");
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,stroke,
                                 _env->NewStringUTF(str.c_str()), pos.X, pos.Y, size);
        }
    }
	
	void DrawName(Color color, float stroke, std::string str, Vector3 pos, float size) {
        
		if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawName",
                                                   "(Landroid/graphics/Canvas;IIIIFLjava/lang/String;FFF)V");
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,stroke,
                                 _env->NewStringUTF(str.c_str()), pos.X, pos.Y, size);
        }
    }
	
    void DrawFilledCircle(Color color, Vector2 pos, float radius) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawfilledcircle = _env->GetMethodID(canvasView, "DrawFilledCircle",
                                                           "(Landroid/graphics/Canvas;IIIIFFF)V");
            _env->CallVoidMethod(_cvsView, drawfilledcircle, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b, pos.X, pos.Y, radius);
        }
    }
	
	void DrawCircle(Color color, float stroke, Vector3 pos, float radius) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawcircle = _env->GetMethodID(canvasView, "DrawCircle",
                                                           "(Landroid/graphics/Canvas;IIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawcircle, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b, stroke, pos.X, pos.Y, radius);
        }
    }
	
	void DrawFilledRect(Color color, Vector3 pos, float width, float height) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawfilledrect = _env->GetMethodID(canvasView, "DrawFilledRect",
                                                           "(Landroid/graphics/Canvas;IIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawfilledrect, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b, pos.X, pos.Y, width, height);
        }
    }
	
	void DrawFilledOval(Color color, Vector2 pos, float width, float height) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawfilledrect = _env->GetMethodID(canvasView, "DrawFilledOval",
                                                           "(Landroid/graphics/Canvas;IIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawfilledrect, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b, pos.X, pos.Y, width, height);
        }
    }
	
    void DrawBox(Color color, float stroke, Rect rect) {
        Vector3 v1 = Vector3(rect.x, rect.y);
        Vector3 v2 = Vector3(rect.x + rect.width, rect.y);
        Vector3 v3 = Vector3(rect.x + rect.width, rect.y + rect.height);
        Vector3 v4 = Vector3(rect.x, rect.y + rect.height);

        DrawLine(color, stroke, v1, v2); // LINE UP
        DrawLine(color, stroke, v2, v3); // LINE RIGHT
        DrawLine(color, stroke, v3, v4); // LINE DOWN
        DrawLine(color, stroke, v4, v1); // LINE LEFT
    }
	
    void DrawCrosshair(Color clr, Vector3 center, float size = 20) {
        float x = center.X - (size / 2.0f);
        float y = center.Y - (size / 2.0f);
        DrawLine(clr, 3, Vector3(x, center.Y), Vector3(x + size, center.Y));
        DrawLine(clr, 3, Vector3(center.X, y), Vector3(center.X, y + size));
    }
};

#endif

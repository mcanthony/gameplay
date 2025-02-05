/*The MIT License (MIT)

Copyright (c) 2015 Jens Malmborg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#include "vertex-declaration.h"

void VertexDeclaration::Setup(ShaderProgram *shaderProgram) {
    int stride = 0;
    for (auto element : elements_) {
        stride += element.offset;
    }
    int offset = 0;
    for (auto element : elements_) {
        auto attribute = glGetAttribLocation(
                shaderProgram->glProgram(), element.name.c_str());
        if (attribute == -1) {
            throw std::runtime_error(
                    "Couldn't find element name '" + element.name + "'");
        }
        // This depends on that the correct vertex buffer has been set.
        glEnableVertexAttribArray(attribute);
        glVertexAttribPointer(attribute, element.size, GL_FLOAT, GL_FALSE,
                              stride, (GLvoid *)offset);
        offset += element.offset;
    }
}

void VertexDeclaration::AddElement(
        std::string name, int size, int offset) {
    elements_.push_back(VertexElement { name, size, offset });
}

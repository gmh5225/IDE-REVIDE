#pragma once

#include <QLineEdit>
#include <QPushButton>

#include "CodeEditor.h"
#include "Styled.h"
#include "GraphDialog.h"
#include "DockManager.h"

class BitcodeHighlighter;
class FunctionDialog;
class DocumentationDialog;

struct LLVMGlobalContext;

namespace llvm
{
class Function;
class BasicBlock;
} // namespace llvm

enum class AnnotationType
{
    Nothing,
    Function,
    BasicBlockStart,
    Instruction,
    BasicBlockEnd,
};

static const char* annotationTypeName[] = {
    "Nothing",
    "Function",
    "BasicBlockStart",
    "Instruction",
    "BasicBlockEnd",
};

struct Annotation
{
    AnnotationType type = {};
    unsigned line = 0;
    const void* ptr = nullptr;
};

struct AnnotatedLine
{
    QString line;
    Annotation annotation;
};

class BitcodeDialog : public ads::CDockManager, Styled<BitcodeDialog>
{
    Q_OBJECT

public:
    CSS_COLOR(keywordColor);
    CSS_COLOR(instructionColor);
    CSS_COLOR(globalVariableColor);
    CSS_COLOR(localVariableColor);
    CSS_COLOR(constantColor);
    CSS_COLOR(integerTypeColor);
    CSS_COLOR(commentColor);
    CSS_COLOR(metadataColor);
    CSS_COLOR(functionColor);

public:
    explicit BitcodeDialog(QWidget* parent = nullptr);
    ~BitcodeDialog();
    bool load(const QString& type, const QByteArray& data, QString& errorMessage);

protected:
    void changeEvent(QEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

private slots:
    void godboltClickedSlot();
    void helpClickedSlot();
    void bitcodeCursorPositionChangedSlot();

private:
    ut64 getBlockId(const llvm::BasicBlock* block);

private:
    CodeEditor* mPlainTextBitcode = nullptr;
    QLineEdit* mLineEditStatus = nullptr;
    QPushButton* mButtonGodbolt = nullptr;
    QPushButton* mButtonHelp = nullptr;

    LLVMGlobalContext* mContext = nullptr;
    BitcodeHighlighter* mHighlighter = nullptr;
    QVector<AnnotatedLine> mAnnotatedLines;
    QVector<int> mFunctionLineMap;
    std::unordered_map<const llvm::BasicBlock*, int> mBlockLineMap;
    std::unordered_map<const llvm::BasicBlock*, QString> mBlockLabelMap;
    QString mErrorMessage = "index out of bounds";
    int mErrorLine = -1, mErrorColumn = -1;
    FunctionDialog* mFunctionDialog;
    DocumentationDialog* mDocumentationDialog;
    GraphDialog* mGraphDialog;
    std::unordered_map<const llvm::Function*, GenericGraph> mFunctionGraphs;
    std::unordered_map<ut64, const llvm::BasicBlock*> mBlockIdToBlock;
    std::unordered_map<const llvm::BasicBlock*, ut64> mBlockToBlockId;
    ut64 mCurrentBlockId = 0;
    ut64 mCurrentGraphId = 0;
    bool mIgnoreCursorMove = false;
    ads::CDockManager* mDockManager = nullptr;
};

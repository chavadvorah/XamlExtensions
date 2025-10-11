# XamlExtensions Roadmap

## Active Development

### High Priority
- [ ] Add error handling/validation to GridLength operations
- [ ] Log warnings when incompatible types are used (Auto + Pixel)
- [ ] Consider fallback values or documented behavior
- [ ] Update IDL comments with operation constraints

### Medium Priority
- [ ] Add unit tests for all operations
- [ ] Test binary operations (Add, Multiply, Divide)
- [ ] Test unary operations (Neg)
- [ ] Test ternary operations (Add3, Multiply3)
- [ ] Test GridLength operations
- [ ] Test divide-by-zero protection
- [ ] Test property change notifications

### Low Priority
- [ ] Consider additional operations based on usage patterns
- [ ] Performance profiling for property change callbacks
- [ ] Documentation improvements (inline XML comments)

---

## Completed ✅

### 2025-10-09: CRTP Refactoring
**Impact:** Eliminated 90%+ code duplication

**Changes:**
- Created `AttachedPropertyHelper.h` with CRTP base template
- Implemented helper macros (DECLARE/IMPLEMENT for unary/binary/ternary)
- Refactored all 9 operations: Add, Multiply, Divide, Neg, Add3, Multiply3, GridLengthAdd, GridLengthAdd3
- Removed GridLengthSum (unused feature)

**Architecture:**
- `AttachedPropertyBase<TDerived, TValue>` - CRTP base template
- Separated implementation type (TDerived) from WinRT projected type (TProjected)
- Operations now only contain operation-specific logic in `UpdateResult` method

**Documentation:**
- Created comprehensive XamlExtensions README
- Documented app.manifest registration requirement
- Added troubleshooting guide

### Earlier Completions
- ✅ Math operations: Add, Multiply, Divide (with zero-check), Neg
- ✅ Multi-input operations: Add3, Multiply3
- ✅ GridLength operations: GridLengthAdd, GridLengthAdd3
- ✅ Attached properties with PropertyChangedCallback for automatic recalculation
- ✅ Namespace aliases in pch.h (mux, muxc, wf)

---

## Technical Debt

### High Priority
**1. Missing Error Handling in GridLength Operations**
- **Issue**: Silent failures when adding Auto + Pixel or Star + Pixel
- **Impact**: Result property not updated, no feedback to developer
- **Recommendation**:
  - Add error logging or throw exceptions for invalid operations
  - Consider fallback values (e.g., return first valid Pixel value)
  - Document behavior in IDL comments
- **Files**: GridLengthAdd.cpp, GridLengthAdd3.cpp
- **Effort**: Low (1-2 hours)

### Medium Priority
**2. No Unit Tests**
- **Issue**: Zero test coverage for critical calculation logic
- **Impact**: Breaking changes aren't caught, refactoring is risky
- **Recommendation**: Add unit tests for all operations
- **Effort**: High (4-6 hours initial setup)

### Low Priority
**3. pch.h Duplicate Includes**
- **Issue**: Some includes may be duplicated or inconsistent
- **Recommendation**: Clean up and document why certain includes are in PCH
- **Effort**: Low (30 min)

---

## Future Considerations

### Potential New Operations
- **Subtract** - A - B (if needed)
- **Min/Max** - Min(A, B) or Max(A, B)
- **Clamp** - Clamp(Value, Min, Max)
- **Lerp** - Linear interpolation
- **Modulo** - A % B

**Decision:** Wait for actual usage needs before adding. Avoid feature creep.

---

*Last updated: 2025-10-11*
